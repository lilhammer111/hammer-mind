# 资源

关于trait:

https://rustmagazine.github.io/rust_magazine_2021/chapter_7/rusts-standard-library-traits.html

关于宏：



# 多线程中按引用获取闭包

`Fn`类型的闭包：

```rust
fn main() {
    let data = vec![1, 2, 3];
    let handle = std::thread::spawn(|| {
        // 这是不合法的，因为闭包试图按引用捕获 `data`
        println!("{:?}", data);
    });
    handle.join().unwrap();
}
```

编译会报错：

>  closure may outlive the current function, but it borrows `data`, which is owned by the current function



这种情况想要按引用捕获，必须确保主线程中`data`变量的引用存活的足够久，并且确保这种捕获在多线程环境中是安全的，可以使用`Arc`和`Mutex`智能指针：

```rust
use std::sync::{Arc, Mutex};
use std::thread;

fn main() {
    // 将 `data` 放入 Arc 和 Mutex 中
    let data = Arc::new(Mutex::new(vec![1, 2, 3]));

    // 克隆 Arc，使得多个线程可以共享所有权
    let data_for_thread = Arc::clone(&data);
    let handle = thread::spawn(move || {
        // 锁定 Mutex 以访问数据
        let mut data = data_for_thread.lock().unwrap();
        data.push(4);
        println!("{:?}", *data);
    });

    // 主线程也可以访问和修改数据
    {
        let mut data = data.lock().unwrap();
        data.push(5);
    }

    handle.join().unwrap();

    // 最终检查数据
    let data = data.lock().unwrap();
    println!("Final data: {:?}", *data);
}

```



# Trait `Any` and `downcast_mut()`

```rust
use std::any::Any;

#[derive(Default)]
struct Point {
    x: i32,
    y: i32,
}

impl Point {
    fn inc(&mut self) {
        self.x += 1;
        self.y += 1;
    }
}

fn map_any(mut any: Box<dyn Any>) -> Box<dyn Any> {
    // downcast_mut 方法可以帮助你在运行时检查和转换 Any 类型的对象。
    // 它通常用于动态类型转换的场景，特别是当你处理一组类型不确定的对象时。
    if let Some(num) = any.downcast_mut::<i32>() {
        *num += 1;
    } else if let Some(string) = any.downcast_mut::<String>() {
        *string += "!";
    } else if let Some(point) = any.downcast_mut::<Point>() {
        point.inc();
    }
    any
}

fn main() {
    let mut vec: Vec<Box<dyn Any>> = vec![
        Box::new(0),
        Box::new(String::from("a")),
        Box::new(Point::default()),
    ];
    // vec = [0, "a", Point { x: 0, y: 0 }]
    vec = vec.into_iter().map(map_any).collect();
    println!("{:?}", vec) // [Any { .. }, Any { .. }, Any { .. }] cause not impl Display trait
    // vec = [1, "a!", Point { x: 1, y: 1 }]
}
```



# generic blanket impls， 泛型覆盖实现

gbi，就是指**使用泛型实现trait**。

看例子：
```rust
trait Even {
    fn is_even(self) -> bool;
}

impl Even for i8 {
    fn is_even(self) -> bool {
        self % 2_i8 == 0_i8
    }
}

impl Even for u8 {
    fn is_even(self) -> bool {
        self % 2_u8 == 0_u8
    }
}

impl Even for i16 {
    fn is_even(self) -> bool {
        self % 2_i16 == 0_i16
    }
}

// etc

#[test] // ✅
fn test_is_even() {
    assert!(2_i8.is_even());
    assert!(4_u8.is_even());
    assert!(6_i16.is_even());
    // etc
}
```

上面为`i8`,`u8`,`i16`每一种类型都实现了`Even`Trait，其实没必要，可以使用GBI来统一为一个泛型`T`实现`Even` trait：

```rust
use std::fmt::Debug;
use std::convert::TryInto;
use std::ops::Rem;

trait Even {
    fn is_even(self) -> bool;
}

// generic blanket impl
impl<T> Even for T
where
    T: Rem<Output = T> + PartialEq<T> + Sized,
    u8: TryInto<T>,
    <u8 as TryInto<T>>::Error: Debug,
{
    fn is_even(self) -> bool {
        // these unwraps will never panic
        self % 2.try_into().unwrap() == 0.try_into().unwrap()
    }
}

#[test] // ✅
fn test_is_even() {
    assert!(2_i8.is_even());
    assert!(4_u8.is_even());
    assert!(6_i16.is_even());
    // etc
}
```



**GBI不能被重写呀！！！**因为这样会引起实现冲突，编译器不知道应该使用GBI还是具体类型的实现。

```rust
impl Even for u8 { // ❌
    fn is_even(self) -> bool {
        self % 2_u8 == 0_u8
    }
}
```



诸如：`impl<E: error::Error> From<E> for Box<dyn error::Error>`这种，并不是严格的GBI，但是可以视为条件泛型实现。

# dbg!宏

想要`dbg!()`，必须先实现Debug宏，当然可以直接derive派生Debug宏。

Debug trait和 Display Trait的签名是一样的：
```rust
trait Debug {
    fn fmt(&self, f: &mut Formatter<'_>) -> Result;
}
```

```rust
trait Display {
    fn fmt(&self, f: &mut Formatter<'_>) -> Result;
}
```

不同点在于：

1. `dbg!`打印到 stderr 而不是 stdout，因此在我们的程序中，能够很容易地和标准输出的输出结果区分。
2. `dbg!`会连同传入的表达式和表达式的计算结果一起打印出来。
3. `dbg!`会获取传入参数的所有权并将其返回，因此你可以在表达式中使用它：

但问题是：

`dbg!`的唯一缺点就是它不会在 release 构建中自动裁剪，所以如果我们不想在最后生成的二进制包含这些内容，就必须手动移除它。



# Eq和PartialEq

Eq比PartialEq多一个` a == a `的自反性。主要针对浮点数中的`NaN`。



# index方法会自动解引用Output

这是`Index` Trait的实现，`index()`函数的签名中告诉我们他返回一个Output的引用（`fn index(&self, index: Idx) -> &Self::Output;`）

```rust
trait Index<Idx: ?Sized> {
    type Output: ?Sized;
    fn index(&self, index: Idx) -> &Self::Output;
}
```

但是实际上，编译器在这里有一个语法糖：
也即他会自动给`&Self::Output`解引用。

例子：

```rust
fn main() {
    let v = vec![1, 2, 3];
    let num = v[0];
}
```

按照函数签名，这里的`num`变量的类型应该是`&i32`，但是实际上这里的`num`却是`i32`类型，是因为，编译器在这里做了解引用：
`let num = v[0]`其实是`let num = *v[0]`。

一个有意思的环绕索引的例子：

```rust
use std::ops::Index;

struct WrappingIndex<T>(Vec<T>);

impl<T> Index<usize> for WrappingIndex<T> {
    type Output = T;
    fn index(&self, index: usize) -> &T {
        &self.0[index % self.0.len()]
    }
}

fn main() {
    let wv = WrappingIndex(vec![1, 3, 5]);
    let val = wv[12];
    println!("{val}")
}
```



# Into Trait

rust为`Into`trait提供了GBI实现，但前提是`T`是一个`From`trait。

```rust
impl<T, U> Into<U> for T
where
    U: From<T>,
{
    fn into(self) -> U {
        U::from(self)
    }
}
```

**`Into<T>`一个常见的用途是，使得需要拥有值的函数具有通用性，而不必关心它们是拥有值还是借用值。**

```rust
struct Person {
    name: String,
}

impl Person {
    // 接受:
    // - String
    fn new1(name: String) -> Person {
        Person { name }
    }

    // 接受:
    // - String
    // - &String
    // - &str
    // - Box<str>
    // - Cow<'_, str>
    // - char
    // 因为上面所有的类型都可以转换为 String
    fn new2<N: Into<String>>(name: N) -> Person {
        Person { name: name.into() }
    }
}
```



# 如何理解Cell？

Cell通过拷贝语义在单线程中实现了不可变变量的内部可变性。
理解：

Cell其实是做了一层**封装**，他控制了语言层面的数据访问，让调用者**不意外**地修改一个变量。

当我希望某个变量是可变时，我会直接这样定义：

```rust
let mut num = 1;
```

但这意味着对于所有人而言，这个`num`是可访问，可修改的，**无论何时何地**。

但这并不暴露该变量的人的初衷，他不希望**无论何时何地**，这个变量都是可修改的，他希望由调用者**审慎**地决定何时何地对该变量进行修改，并且，非常清楚自己此时的修改行为。

换句话说，如果这个变量是可变的，那调用者可以使用基本的赋值语句就可以修改，这是语言上的能力，这导致了调用者有可能会在不该修改变量值的时候修改，而使用Cell包裹，相当于让调用者更审慎，他无法随意的使用赋值语句进行修改变量，他必须要主动调用.set()方法，当他这样调用的时候，意味着他知道他在此处调用是合理的，这就是Cell的设计哲学。



cell还有一个应用场景，也即在闭包中，如果函数入参要求是一个实现了Fn Trait的闭包，而闭包需要修改捕获到的某个数据，这时就会遇到一个问题，就是如果闭包修改了该数据，则闭包就是实现了FnMut类型的数据了，这样不满足入参类型了，要解决这个问题就是使用Cell包裹该数据，实现内部可变性，这个时候闭包就是只实现了Fn trait了，这样既满足了修改数据的需求，也符合了函数入参约束。

# Move和Fn 等Trait

move关键字只决定捕获方式，不决定闭包实现了哪个Trait，当使用move关键字时，被捕获变量所有权转移到闭包中，注意copy语义：

```rust
fn main() {
    let x = String::from("Hello");
    let clo = move || println!("{}", x);
    println!("{}", x);  // 这会编译报错，因为x已经被转移到闭包了
    clo();
}
```

而如果x是一个实现Copy Trait的类型，上述第三行不会报错：
```rust
fn main() {
    let x = 10;
    let clo = move || println!("{}", x);
    println!("{}", x * 2); // 不会报错，闭包通过copy语义捕获x
    clo();
}
```



# 如何区分Fn, FnOnce, FnMut？

`FnMut`最容易区分，如果闭包捕获外部变量，并且修改了该变量，即实现了`FnMut`。



但是`Fn`和`FnOnce`都是不可修改捕获的变量，鉴别他们俩主要看，这个闭包是否被作为函数传参传递给另一个函数，并且该参数的bound要求是FnOnce，那这个闭包就实现`FnOnce`，比如：
```rust
fn consume_clo<F: FnOnce>(f: F) {
    f();
}

let print_clo = || println!("Hello FnOnce");

comsume_closure(print_clo);

// 如果我们想要继续使用 print_clo 这个闭包的话，就会报错，因为编译器通过前面的推断，发现print_clo是一个实现了FnOnce这个trait的闭包
print();  // 编译不通过
```



# 如何理解异步中的“阻塞”？

https://chatgpt.com/share/4a741d5f-be54-4760-affd-03385cb0f2bf





# 满足'static生命周期的例子

在 Rust 中，具有 `'static` 生命周期的值或类型是那些在程序的整个生命周期中都有效的值或类型。一般来说，以下几种情况的值或类型会具有 `'static` 生命周期：

1. 基本类型和常量

基本类型（如 `i32`、`f64`、`bool` 等）和常量（`const` 关键字定义的值）都具有 `'static` 生命周期，因为它们不包含任何引用。

```rust
const PI: f64 = 3.1415;
let x: i32 = 42;
```

2. 具有 `'static` 生命周期的结构体和枚举

如果结构体或枚举的所有字段都是 `'static` 的，那么该结构体或枚举也是 `'static` 的。

```rust
struct MyStruct {
    a: i32,
    b: bool,
}

enum MyEnum {
    Variant1(i32),
    Variant2(bool),
}
```

3. 静态变量

用 `static` 关键字声明的全局变量具有 `'static` 生命周期。

```rust
static GLOBAL: i32 = 100;
```

4. 所有权的字符串字面量

字符串字面量（例如 `"hello"`）具有 `'static` 生命周期，因为它们在程序的整个生命周期内都是有效的。

```rust
let s: &'static str = "hello";
```

5. 无引用的 Box<T>

`Box<T>` 类型本身是一个智能指针，用于在堆上分配内存。如果 `T` 是 `'static` 的，那么 `Box<T>` 也是 `'static` 的。

```rust
let boxed: Box<i32> = Box::new(5);
```

6. 没有非 `'static` 引用的泛型类型

如果一个泛型类型 `T` 不包含任何非 `'static` 引用，那么它就是 `'static` 的。

```rust
struct Container<T> {
    value: T,
}

let container: Container<i32> = Container { value: 10 };
```

实验：
```rust
use std::fmt::Debug;

fn print_it<T: Debug + 'static>(input: &T) {
    println!("'static value passed in is: {:?}", input);
}

#[derive(Debug)]
struct Container<T> {
    #[allow(dead_code)]
    elem: T,
}


fn main() {
    let container = Container {
        elem: 1
    };
    print_it(&container);
}
```

7. 函数指针

函数指针类型本质上是指向代码的指针，具有 `'static` 生命周期。

```rust
fn my_function() -> i32 { 42 }
let fn_ptr: fn() -> i32 = my_function;
```

8. 没有引用或只包含 `'static` 引用的闭包

闭包可以具有 `'static` 生命周期，如果它们不捕获任何非 `'static` 引用。

```rust
let x = 5;
let closure = move || x + 1;
```

特殊情况:

有些类型可能不是显而易见的具有 `'static` 生命周期，但在特定情况下会被认为是 `'static` 的。

具有 `'static` 生命周期的 Trait 对象:

如果 Trait 对象的所有实现类型都具有 `'static` 生命周期，那么这个 Trait 对象也是 `'static` 的。

```rust
use std::fmt::Debug;

fn print_it(input: Box<dyn Debug + 'static>) {
    println!("{:?}", input);
}

fn main() {
    let value = Box::new(42);
    print_it(value);
}
```

> 总结:
>
> 在 Rust 中，具有 `'static` 生命周期的值或类型是那些在程序的整个生命周期中都有效的值或类型。了解哪些类型具有 `'static` 生命周期对于编写健壮的 Rust 代码非常重要。基本类型、常量、静态变量、字符串字面量、没有引用或只包含 `'static` 引用的结构体和枚举、Box 指针和函数指针都具有 `'static` 生命周期。



# UTF8和str

这是一个关于 **UTF-8 编码** 的核心问题：底层是如何知道每个 Unicode 字符应该使用 1、2、3 还是 4 个 `u8` 来表示。这是通过 **每个字节的前几位（前缀位）** 来区分的，UTF-8 编码设计了明确的规则，依赖于这些前缀来确定每个字符所占用的字节数。

### 1. UTF-8 编码规则

UTF-8 是一种 **自解释** 的编码格式。每个字节的前几位决定了该字符使用的总字节数，并且后续字节的格式也有固定的模式。

具体来说：

- **1 字节**：用于编码 U+0000 到 U+007F 的字符，也就是标准的 ASCII 字符。编码规则是：`0xxxxxxx`。其中，`0` 是前缀位，表示该字符占用 1 个字节。
  
- **2 字节**：用于编码 U+0080 到 U+07FF 的字符。第一个字节的格式是：`110xxxxx`，表示该字符占用 2 个字节。后续的字节以 `10xxxxxx` 的格式开头。

- **3 字节**：用于编码 U+0800 到 U+FFFF 的字符。第一个字节的格式是：`1110xxxx`，表示该字符占用 3 个字节。后续的字节也是 `10xxxxxx` 开头。

- **4 字节**：用于编码 U+10000 到 U+10FFFF 的字符。第一个字节的格式是：`11110xxx`，表示该字符占用 4 个字节。后续字节同样以 `10xxxxxx` 开头。

### 2. UTF-8 编码的具体格式

| 字节数 | Unicode 代码点范围  | 字节 1   | 字节 2   | 字节 3   | 字节 4   |
| ------ | ------------------- | -------- | -------- | -------- | -------- |
| 1      | U+0000 到 U+007F    | 0xxxxxxx |          |          |          |
| 2      | U+0080 到 U+07FF    | 110xxxxx | 10xxxxxx |          |          |
| 3      | U+0800 到 U+FFFF    | 1110xxxx | 10xxxxxx | 10xxxxxx |          |
| 4      | U+10000 到 U+10FFFF | 11110xxx | 10xxxxxx | 10xxxxxx | 10xxxxxx |

### 3. 如何通过字节来判断字符的长度？

在 UTF-8 编码中，每个字符的第一个字节会告诉我们字符占用了多少个字节。具体判断规则如下：

- **如果第一个字节的最高位是 `0`**，表示这是一个 1 字节的字符（ASCII 范围内）。
  
- **如果第一个字节以 `110` 开头**，表示这是一个 2 字节的字符，后面跟着一个字节。
  
- **如果第一个字节以 `1110` 开头**，表示这是一个 3 字节的字符，后面跟着两个字节。
  
- **如果第一个字节以 `11110` 开头**，表示这是一个 4 字节的字符，后面跟着三个字节。

所有后续字节的前两位都应该是 `10`，这是 UTF-8 的约束之一，确保这些字节可以正确识别为多字节字符的一部分。

### 4. 实例解析

让我们通过几个实例来解析如何使用这些前缀来区分不同字节数的字符。

#### a) 单字节字符：`A`

字符 `A` 的 Unicode 代码点是 `U+0041`。在 UTF-8 中，它使用一个字节编码，因为它在 U+0000 到 U+007F 范围内。

- `A` 的二进制表示是 `01000001`。
- 在 UTF-8 中，符合 `0xxxxxxx` 的规则，所以它只使用 1 个字节，即 `0x41`。

#### b) 两字节字符：`¢`（分币符号）

字符 `¢` 的 Unicode 代码点是 `U+00A2`。它的编码过程如下：

- 它的二进制表示是 `10100010`，处于 U+0080 到 U+07FF 之间，需要 2 个字节。
- 根据 UTF-8 的编码规则，第一个字节是 `110xxxxx`，第二个字节是 `10xxxxxx`。
- 将 `U+00A2` 按照 UTF-8 规则编码为：`11000010 10100010`，即 `0xC2 0xA2`。

#### c) 三字节字符：`€`（欧元符号）

字符 `€` 的 Unicode 代码点是 `U+20AC`。它的编码过程如下：

- 它的二进制表示是 `10000010101100`，处于 U+0800 到 U+FFFF 范围内，需要 3 个字节。
- 第一个字节是 `1110xxxx`，表示 3 字节的字符，后续字节是 `10xxxxxx`。
- 将 `U+20AC` 按照 UTF-8 规则编码为：`11100010 10000010 10101100`，即 `0xE2 0x82 0xAC`。

#### d) 四字节字符：`😊`（笑脸表情）

字符 `😊` 的 Unicode 代码点是 `U+1F60A`。它的编码过程如下：

- 它的二进制表示是 `11111011000001010`，处于 U+10000 到 U+10FFFF 范围内，需要 4 个字节。
- 第一个字节是 `11110xxx`，表示 4 字节的字符，后续字节是 `10xxxxxx`。
- 将 `U+1F60A` 按照 UTF-8 规则编码为：`11110000 10011111 10011000 10001010`，即 `0xF0 0x9F 0x98 0x8A`。

### 5. Rust 中如何解析 UTF-8 字符

在 Rust 中，字符串（`&str` 或 `String`）默认使用 UTF-8 编码。当你遍历或操作字符串时，Rust 底层会根据 UTF-8 编码规则自动处理字符的字节数。

```rust
fn main() {
    let s = "😊";  // U+1F60A, 4字节字符
    for b in s.bytes() {
        println!("{:08b}", b);  // 按二进制输出每个字节
    }
}
```

输出：
```
11110000
10011111
10011000
10001010
```

在这个例子中，Rust 根据 UTF-8 的规则，正确地将 `😊` 识别为 4 字节字符，并输出其二进制编码。

### 总结

UTF-8 编码的自解释性使得每个字节的前几位就能告诉我们接下来需要多少字节来表示一个字符。通过分析每个字节的前缀，底层系统能够判断字符的长度：

- 1 字节：`0xxxxxxx`（ASCII）
- 2 字节：`110xxxxx 10xxxxxx`
- 3 字节：`1110xxxx 10xxxxxx 10xxxxxx`
- 4 字节：`11110xxx 10xxxxxx 10xxxxxx 10xxxxxx`

这种机制确保了 UTF-8 的紧凑性和灵活性，可以高效地处理不同长度的字符。
