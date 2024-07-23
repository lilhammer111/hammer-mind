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

