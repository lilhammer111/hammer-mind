# 一些重要的参考

书：

- [Rust语言圣经](https://course.rs/about-book.html)

练习：

- [rust-by-practice](https://github.com/sunface/rust-by-practice/tree/master)

# 命名规范

rust命名规范参考该文档：https://course.rs/practice/naming.html



# 变量绑定

在Rust中的变量绑定等同于其他语言的“赋值”，Rust使用“绑定”一词的用意无外乎与其“所有权”概念保持一致。变量绑定的关键词为`let`，例如：

```rust
fn main() {
    let a = 1;
    println!("{}", a)
}
```



# 类型注解（Annotation）

在声明变量时，rust使用annotatin来显式声明变量的类型：

```rust
let some_number: i32 = 5;
```



for test

# mut

使用`mut`关键字声明的变量才可变

```rust
fn main() {
    let mut x = 1;
    x = 27;
    println!("{}", x)
}
```



```rust
fn main() {
    let x = 5;
    println!("The value of x is {}", x); 
    
    x = 6; // 编译报错， 因为x变量没有使用mut关键字修饰，所以不可变。
    println!("The value of x is {}", x); 
}
```



# 常量（const）

常量不可以类型推断，所以常量的类型必须显示标注，如`const PI:f64 = 3.14;`。

常量当然不可以使用`mut`关键字。

常量必须在编译时就有已知的固定值，不能是运行时才能确定的结果。



# 覆盖（shadowing）

Rust的shadowing特性在Rust圣经中被译为“变量遮蔽”，然而我更喜欢使用“变量覆盖”，简单理解就是如果出现同名变量，则后者覆盖前者。

shadowing可以解决相同作用域下变量类型转换时需重新命名的问题，比如原先字符串类型的age变量要转成整数类型，可能会需要额外使用一个age_int变量来接收（或者说绑定吧），但是rust的shadowing特性可以让事情变得简单，即使在相同作用域下，Rust也允许使用同名变量来“装载”另一种数据类型的值，但同时也意味着原先的同名变量已经被现在这个所“覆盖”。

使用方法很简单就是使用`let`关键字修饰同名变量，比如：

```rust
fn main() {
    let age = String::from("25");
    let age = 35;
    
    println!("age: {}", age)
}
```



这样是错的，因为没有使用`mut`关键字修饰变量`x`让他成为可变变量：

```rust
fn main() {
    let x = 5;
    println!("The value of x is {}", x); 
    
    x = 6;
    println!("The value of x is {}", x); 
}
```

但如果我们此时使用`let`修饰同名变量`x`，则就是shadowing:

```rust
fn main() {
    println!("Hello, world!");

    let x = 5;
    println!("The value of x is {}", x); 
    
    x = 6;
    println!("The value of x is {}", x); 
}
```

但是实际上，下面这个例子更符合shadowing设计的初衷，第一个spaces是str类型，第二个spaces通过let修饰后，利用了shadowing的特性转成了int类型，这在别的静态语言是很难实现的：

```rust
let spaces = " ";
let spaces = spaces.len();
println!("{}", spaces);
```

# 标量类型

标量类型有四种，分别是**浮点类型**，**整数类型**，**布尔类型**，**字符类型**。

# 类型后缀

整数类型中，除了byte类型之外，整数字面值都可以有类型后缀，如57u8。

# 环绕

调试模式下，整数溢出会panic，release模式下，不会panic，而会执行环绕操作：对于u8，256变成0，257变成1

# 浮点类型

浮点类型的默认类型是f64，因为现代CPU上f64和f32的速度差不多，而且精度更高。

# 字符类型

rust中的字符类型是unicode的标量值，比ASCII码更多的字符内容：拼音，中日韩文，零长度空白字符，emoji表情等。

U+0000 到 U+D7FF

U+E000 到 U+10FFFF

# 复合类型

有两种基础的复合类型，一个是**tuple**还有一个是**数组**。

# Tuple

长度固定。

tuple可以存不同类型。

声明方式：

```rust
let tup: (i32, f64, u8) = (500, 6.4, 1);
println!("{} {} {}", tup.0, tup.1, tup.2);
```

tuple可以解构（或者说是模式匹配）。

```rust
let (x, y, z) = tup;
println!("{} {} {}", x, y, z);
```

# 数组

类型固定，长度固定。

声明方式一：

```rust
let a = [1, 2, 3, 4, 5]; 
```

声明方式二：

```rust
let a = [3;5]; // equal to let a = [3, 3, 3, 3, 3];
```

因为其类型和长度固定，数组保存在stack上而不是heap上。 

数组的类型标注：

```rust
let a : [i32; 5] = [1, 2, 3, 4, 5];
```

# statement 和 expression 的区别

statement以分号结尾，expression不以分号结尾。

在c中可以将赋值语句赋值给一个变量，例如：
```c
#include <stdio.h>

int main()
{
    int a, b;
    a = b = 1;
    printf("%d %d", a, b);
}
```

但是在`rust`中，这样是不可以的，编译器会报错，比如：

```rust
fn main() {
    let x = (let y = 5;);
}
```

因为`let y = 5;`是一个`statement`，但是这种情况是Ok的：

```rust
fn main() {
    let x = 5;
    let mut y = {
        let x = 1;
        x // 注意这里没有分号，y此时应该是等于方括号作用域的临时变量x的值，也即1，此时x也是方括号这个作用域的返回值，并且被赋值给了y
    }
 	
    
    
    println!("y: {}", y)
}
```

# 函数

声明关键字fn。

定义参数是必须为每个参数指明类型。

```rust
fn my_func(x: i32, y: i32) {
    println!("{} {}", x, y);
} 
```

# 函数返回值

rust是多返回值的。

 函数返回值声明方式：`-> i32`，例如：

```rust
fn plus_five(x: i32) -> i32 {
    x + 5
}
```

在 Rust 中，函数的返回值可以通过两种方式指定：使用 `return` 关键字或者利用表达式的值。Rust 的一个独特之处在于它允许函数通过最后的表达式来隐式返回值，而不一定需要 `return` 关键字。这种机制使得 Rust 的函数写法更加灵活和表达性强。

在函数中使用 `return` 关键字显式返回一个值。这种方式在从函数的中间位置提前返回时特别有用。例如：

```rust
fn check_number(x: i32) -> String {
    if x > 0 {
        return "Positive".to_string();
    } else if x < 0 {
        return "Negative".to_string();
    }
    return "Zero".to_string();
}
```

如果函数的最后一个语句是一个表达式，该表达式的值会被自动作为函数的返回值。在这种情况下，不需要使用 `return` 关键字，也不需要在表达式后面加上分号（`;`），因为加上分号会将其变成一个语句，而语句不返回值。例如：

```rust
fn add_one(x: i32) -> i32 {
    x + 1
}
```

# 文档注释

# if expression

`if`的condition条件必须是`bool`类型。

# loop

# 所有权

**rust内存管理的原理：**

传统的垃圾收集（GC）机制确实涉及到在程序运行时进行内存管理的过程。这通常由一个或多个后台线程实现，这些线程并行于应用程序的主线程运行。这些  GC  线程的任务是跟踪内存分配，识别不再被应用程序使用的内存（即不可达的对象），并释放这些内存以供再次使用。这个过程是自动的，意味着开发者不需要手动管理内存的生命周期。

相比之下，Rust 的内存管理机制是在编译时静态决定的。Rust 的所有权系统、借用检查和生命周期分析是编译器的一部分，旨在编译时期就确保内存使用的安全性和效率，而不是依赖运行时的垃圾收集器。

因此，在 Rust 中，内存的分配和释放是根据**程序的控制流**和**作用域规则**在**编译时**就已经确定的，不需要运行时的垃圾收集线程介入。这种方法提供了无GC暂停的执行环境，同时减少了运行时开销，提高了性能和预测性。

**所有权规则**：

- 每个值都属于一个变量，这个变量就是这个值的所有者
- 每个值同时只能有一个所有者
- 当所有者超出作用域scope时，则该值被删除

**drop函数：**当变量走出作用域时会自动调用drop函数。

# String类型

String类型在heap上分配内存，并且能保存**在编译时**未知大小的值。

使用`from()`函数从字符串字面值创建String类型的值。

例如：

```rust
fn main() {
    println!("Hello, world!");
    
    let mut s = String::from("Hello");
    
    s.push_str(", World 2 !");
    
    println!("{}", s); 
} 
```

# 移动（Move）

看这个例子：

```rust
fn main() {
    println!("Hello, world!");
    
    let s1 = String::from("hello");
    
    let s2 = s1;
    
    println!("{}", s1);  // 这句话实际上会编译不通过
}

```

如下图，当执行`let s2 = s1`时，浅拷贝的设计会采取这样的做法：复制一份下图中的“结构体”给`s2`，并让`s2`的指针成员变量指向Heap上的字符数组（即下图右边部分）。

但是，如果`s1`，`s2`都离开了作用域，rust会尝试释放相同的内存，这样可能会导致double free（二次释放），因此rust并没有采用这种设计，而是使用了一种名为“移动”的设计理念，当执行`let s2 = s1`，实际上，rust会复制一个s1，也即s2，同时让s1失效，这样就只有s2指向了heap中的那个字符数组，这样是为什么上面这段代码中`println!("{}", s1);`会编译不通过的原因，因为此时s1已经失效了。

 <img src="/home/lilhammer/snap/typora/86/.config/Typora/typora-user-images/image-20240207152132110.png" alt="image-20240207152132110" style="zoom:30%;" />

如果我们强行编译上面这段代码，编译器会报这样的错误:

````
 error[E0382]: borrow of moved value: `s1`
````

**这个例子隐含了一个rust的设计理念，即，rust不会自动创建数据的深拷贝。**

# 克隆（Clone）

如果我们想对上面的例子中的s1进行深度拷贝，我们可以使用`clone()`方法。

```rust 
fn main() {
    println!("Hello, world!");
    let s1 = String::from("hello");
    let s2 = s1.clone();
    println!("s1: {}, s2: {}", s1, s2); // 此时编译就通过了，并且也不会编译报错
}
```

其实这里s1的stack和heap数据都被复制了一份，如图：

<img src="/home/lilhammer/snap/typora/86/.config/Typora/typora-user-images/image-20240207161349138.png" alt="image-20240207161349138" style="zoom:33%;" />

# 复制（Copy）

如果一个类型实现了copy trait，那么旧的变量就可以在赋值后继续使用，比如：

```rust
fn main() {
    let x = 5;
    let y = x; // 这里并没有发生move，而是发生了copy，所以x还是可用的
    println!("x = {}, y = {}", x, y); // 编译不会报错
}
```

标准变量类型都是实现了copy trait的。

如果一个类型或者该类型的一部分实现了Drop trait，那rust就不允许它再去实现Copy trait，否则编译时报错。

任何需要分配内存或资源的类型都不可以实现Copy trait。

# 引用 

类似于传递指针，但是传递引用给函数，值的所有权并不会转移至函数的形参变量。

传递引用给函数，也称为**借用**。

引用和变量一样，在默认情况下也是immutable的，想要修改引用必须满足两个条件：

1. 变量被`mut`关键字修饰。

2. 引用的变量也被`&mut`关键字修饰。

例子：

```rust
fn main(){
    let mut s1 = String::from("Hello");
    let len culate_length(&mut s1);
    println!("The length of '{}' is {}", s1, len);
}

fn calculate_length(s: &mut String) -> usize {
    s.push_str(", world");
    s.len()
}
```

两个“同时”限制：

1. 不可以同时存在两个可变引用（并发安全）。
2. 不可以同时存在一个可变引用和一个不可变引用，因为不可变引用失去意义。

# 借用规则

总的来说，借用规则如下：

- 同一时刻，你只能拥有要么一个可变引用, 要么任意多个不可变引用
- 引用必须总是有效的

这里“引用必须总是有效的”是指被引用的数据必须有效，不能被释放或者回收，也即被引用的数据的生命周期要大于引用的生命周期。

# 引用与借用的区别

在 Rust 中，**引用**和**借用**这两个术语经常一起使用，它们密切相关但有细微的区别。理解这两个概念对于掌握 Rust 的内存安全特性至关重要。

**引用：**

**引用**是一种类型特性，它允许你访问或修改数据而无需取得数据的所有权。在 Rust 中，使用 `&` 符号创建一个引用，这意味着你是在引用某个值的地址而不是值本身。引用主要有两种形式：

- **不可变引用**（`&T`）：允许你读取数据但不能修改它。Rust 的规则是你可以有任意数量的不可变引用，因为它们不会引起数据的改变。
- **可变引用**（`&mut T`）：允许你修改引用的数据。为了保证内存安全，Rust 规定在特定作用域中，特定数据只能有一个活跃的可变引用，这防止了数据竞争。

**借用：**

**借用**是一种机制，通过这种机制，所有权或修改权限可以临时转移给另一个变量。在 Rust 中，当你创建一个引用时，实际上是在进行借用。借用有两种类型，与引用的两种形式相对应：

- 当你创建一个不可变引用时，你是在**借用**值，但承诺不会修改它。
- 当你创建一个可变引用时，你是在**可变借用**值，此时你可以修改它，但这需要满足 Rust 的借用规则，即在特定作用域中对特定数据只能有一个活跃的可变引用。

**关系和区别**：

所以，**引用**是一种语法和类型特性，使得借用成为可能。**借用**是一个概念或机制，描述了如何使用引用来临时访问或修改数据，而不违反所有权规则。引用是实现借用机制的工具。

总结来说，引用和借用在 Rust 中是紧密相关的：引用是实现借用概念的语法手段，而借用是 Rust 用来保证代码内存安全的一种规则和机制。通过这种方式，Rust 既保证了内存安全，又避免了垃圾收集器的开销，实现了高效的内存管理。

# 悬空引用（Dangling Reference）

悬空引用是指指针所指向的数据被销毁，但是指针依然存在。

`rust`在编译阶段就禁止了悬空引用的发生。如果引用了某个数据，那么编译器会保证在引用离开作用域之前，数据不会离开作用域。

例如下面这个例子，`dangle()`函数中的&s是s的一个引用，&s作为函数的返回值将所有权转移给了r，但是s的作用域已经结束了，s被销毁了，这就可能会产生悬空指针，因此编译不通过：

```rust
fn main() {
    let r = dangle();
}

fn dangle() -> &String { // 编译不通过
    let s = String::from("hello");
    &s  
}
```

编译会报错： 

```
error[E0106]: missing lifetime specifier 
```

# 切片（Slice）

切片的关键字是&，就跟c语言中的指针一样。

&中存储的就是数组起始位置的内存地址，以及一个数组长度。

slice不持有所有权。

# 字符串切片 &str

**形式：** [start_index .. end_index]，左包含，右不包含。

注意：字符串切片的范围索引必须发生在有效的UTF-8字符边界内。如果尝试从一个多字节的字符中创建字符串切片，程序会报错。

字符串字面值的类型就是字符串切片，`&str`就是字符串切片的关键字。

```rust
let s = "hello world!";
```

注意区别，下面的`s`是一个字符串类型，而不是字符串切片：

```rust
let s = String::from("hello world!");
```

# Struct

声明方式：

```rust
struct User {
    username: String,
    email: String,
    sign_in_count: u64,
    active: bool,
}
```

实例化：

```rust
fn main() {
    println!("Hello world!");
    let user1 = User {
        email: String::from("wwwwwwdemon@gmail.com"),
        username: String::from("lilhammer"),
        active: true,
        sign_in_count: 556,
    };
}
```

必须**全量赋值**，否则编译器报错。

字段的访问方式为**点标记法**，即`user1.email`。

想要修改struct中某个字段的值必须在实例化的时候使用`mut`修饰该struct。

```rust
let mut user2 = User {
    email: String::from("wwwwwwdemon@gmail.com"),
    username: String::from("lilhammer"),
    active: true,
    sign_in_count: 556,
}
```

当字段名和字段值的变量名相同时可以简写：

```rust
fn build_user(email: String, username: String) -> User {
    User {
        email,
        username,
        active: true,
        sign_in_count: 0,
    }
}
```

**struct更新语法：**

当想基于已存在的结构体实例创建新实例的时候，比如下面这种情况，其中`email`和`username`是新值，而`active`和`sign_in_count`的值来自user1：

例如，对于下面这个struct：

```rust
let user2 = User {
    email: String::from("helloworld@gmail.com"),
    username: String::from("hello_world"),
    active: user1.active,
    sign_in_count: user1.sign_in_count,
};
```

可以使用更新语法来简化上面的代码：

```rust
let user2 = User {
    email: String::from("helloworld@gmail.com"),
    username: String::from("hello_world"),
	..user1
};
```

# Tuple Struct

声明方式：

```rust
struct Color(i32, i32, i32);
let black = Color(0， 0， 0);
```

# Unit-Like Struct

没有任何字段的结构体。有点类似于空结构体，意义类似。  

# 打印结构体

```rust
#[derive(Debug)]
struct Rectangle {
    width: u32,
    length: u32,
}

fn main() {
	let rect = Rectangle {
        width: 30,
        length: 50,
    };
    println!("{:#?}", rect);
}
```

# 方法

例子：

```rust
struct Rectangle {
    width: u32,
    length: u32,
}
impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.length
    }
}

fn main() {
    let rect = Rectangle {
        width: 30,
        length: 50,
    };
    println!("{}", rect.area());
}
```

# 关联函数

关联函数就是定义在`impl`块中的函数，第一个参数不是`self`。

例如： `String::from()`

关联函数通常用于构造器（函数）。

调用方式：

```rust
struct Rectangle {
    width: u32,
    length: u32,
}
impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.length
    }
    
    fn square(side: u32) -> Rectangle {
        Rectangle {
            width: side,
            length: side,
        }
    }
}

fn main() {
    let square = Rectangle::square(10);
}
```

# 枚举

我们把枚举所有可能值叫做枚举变体。

用法：

```rust
enum IpAddrKind {
    V4,
    V6
}

fn main() {
    let fout = IpAddrKind::V4;
    let six = IpAddrKind::V6;
    route(four);
    route(six);
    route(IpAddrKind::v4); 
}

fn route(ip_kind: IpAddrKind) {}
```

枚举的变体中还可以嵌入其他类型，如：

```rust
enum IpAddrKind {
    V4(u8, u8, u8, u8),
    V6(String),
}

fn main() {
    let home = IpAddrKind::V4(127, 0, 0, 1);
    let loopback = IpAddrKind::V6(String::from("::1"));
}
```

标准库中的`IpAddr`:

```rust
struct Ipv4Addr {
    // --snip--
}

struct Ipv6Addr {
    // --snip-
}

enum IpAddr {
    V4(Ipv4Addr),
    V6(Ipv6Addr),
}
```



}

使用`impl`关键字为枚举定义方法：

```rust
enum Message {
    Quit, // 没有关联任何其他数据
    Move { x: i32, y: i32 }, // 关联了一个结构体
    Write(String), 
    ChangeColor(i32, i32, i32),
}

// 使用impl关键字为枚举定义方法
impl Message {
    fn call(&self) {}
}

fn main() {
    let q = Message::Quit;
    let m = Message::Move { x: 12, y: 24};
    let w = Message::Write(String::from("Hello"));
    let c = Message::ChangeColor(0, 255, 255);
    
    m.call();
}
```

# Option 枚举

option枚举是定义在标准库中的。

Option枚举是在Prelude预导入模块中。



rust中没有null，null的问题是，当你想像使用非NULL值那样使用NULL值的时候就会引起错误，类似于空指针引用。Rust取而代之的是一个Option\<T>的枚举。

Option\<T>的结构：

```rust
enum Option<T> {
	Some(T),
    None,
}
```

意思是，某个值可能存在也可能不存在。

`Option<T>`，`Some(T)`以及None都可以直接使用，不需要使用命名空间前缀，因为他们都在Prelude预导入模块中。

这样设计的原因是将某个类型的null和某个类型本身给区别开来，以后null就是null，某个类型就是某个类型，而不存在某个类型的null这种概念。

例如这种情况，编译就不通过：
```rust
fn main(){
    let x: i8 = 5;
    let y: Option<i8> = Some(5);
	
    let sum = x + y; // x, y不是同类型，不能进行运算
}
```

# match

模式匹配的例子，match coin后花括号中的每一项都是一个模式。

```rust
enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter,
}

fn value_in_cents(coin: Coin) -> u8 {
    match coin {
        Coin::Penny => {
            println!("Penny!");
            1   
        }
        Coin::Nickel => 5,
        Coin::Dime => 10, 
        Coin::Quarter => 25, 
    }   
}


fn main() {
    value_in_cents(Coin::Penny);    
}
```

match与Option<T>结合的例子：

```rust
fn main() {
    let five = Some(5);
    let six = plus_one(five);
    let none = plus_one(None);
}

fn plus_one(x: Option<i32>) -> Option<i32> {
	match x {
        None => None,
        Some(i) => Some(i + 1),
    }
}
```

**match匹配必须穷举所有模式。**

`_`下划线通配符可以匹配所有其余情况。

```rust
fn main() {
    let n = 0u8;
    match n {
        1 => println!("one"),
        2 => println!("two"),
        3 => println!("three"),
        4 => println!("four"),
        _ => (),
    }
}
```

# If let

例子：

```rust
fn main() {
    let v = Some(0u8);
    if let Some(3) = v {
        println!("three");
    } 
}
```

这个等价于：

```rust
fn main() {
    let v = Some(0u8);
    match v {
        Some(3) => println!("three"),
        _ => (),  
    }
}
```

`if let`语句也可以搭配`else`关键字使用，达到上面`_`通配符相同的作用：

```rust
fn main() {
    let v = Some(0u8);
    if let Some(3) = v {
        println!("three");
    } else {
        println!("others");
    }
}
```



# 生命周期

引用所指向的数据一定要比引用活得更久，否则就会发生悬垂指针这种不安全的情况。

```rust
{
    let r;

    {
        let x = 5;
        r = &x; 
    } // r所指向的数据x在这里就“死了”

    println!("r: {}", r); // 但是r在这里还活着，就违反了： 引用所指向的数据一定要比引用活得更久
}
```



这个函数返回了一个引用：

```rust
fn longest(x: &str, y: &str) -> &str {
    if x.len() > y.len() {
        x
    } else {
        y
    }
}

```

当一个函数返回引用时，我们就需要为这个函数标注生命周期，因为这个函数的调用可能是以下这几种情况：

情况一：

```rust
fn main() {
    let string1 = String::from("long string is long");
    let result;
    {
        let string2 = String::from("xyz");
        result = longest(string1.as_str(), string2.as_str());
    }
    println!("The longest string is {}", result);
}
```

情况二，我们把`main()`中第一句代码和第三句代码互换位置：

```rust
fn main() {
    let string2 = String::from("xyz");
    let result;
    {
        let string1 = String::from("long string is long");
        result = longest(string1.as_str(), string2.as_str());
    }
    println!("The longest string is {}", result);
}
```

我们知道，result实际指向的是两个字符串中更短的那个，也就是string2，所以只要string2活得比result这个引用更久就行了，在情况一种，string2已经在花括号的作用域内“死了”，但是result这个引用还活着，这是不安全的！但是在情况二中，string2就一直活着，跟result活得一样久，这很安全！

所以说，不同的调用环境可能会产生不同的结果（安全或者不安全）！

但我们要确保代码是安全的，咋整？现在假设你是rust编译器，你会怎么解决这个问题？你总不能先运行这段代码试试看吧？有没有什么简单的办法？

有没有这么一种可能，你（一个编译器）心想：开发者啊，你帮我把这个函数返回的引用设置一个假的生命周期，因为函数返回的引用只能从参数中来，那就只能是



这些分析都是我们人为地在这两个特定例子中去尝试调用`longest()`这个函数得出来的结果。但对于这个函数而言，并不是只有上面这两个情况的调用环境的，换句话说，调用环境是未知的，那编译器就不能确定返回的引用是x还是y了。甚至，对于我们开发者，我们尚且还知道这个`longest()`函数的返回值（也就是`&str`）他所指向的要么是string1要么是string2，所以result这个引用要比这两个

我们并不知道调用他的外部环境是否是类型安全的，因此我们应该给



# Package



# Crate



# Module

例子：

```rust
// src/lib.rs
mod front_of_house {
    mod hosting {
        fn add_to_waitlist() {}
        fn seat_at_table() {}
    }

    mod serving {
        fn take_order() {}
        fn serve_order() {}
        fn take_payment() {}
    }
}

```



# Path

例子：

```rust
mod front_of_house {
    mod hosting {
        fn add_to_waitlist() {}
    }
}

pub fn eat_at_restaurant() {

    crate::front_of_house::hosting::add_to_waitlist(); // 绝对路径

    front_of_house::hosting::add_to_waitlist(); // 相对路径
}
```

# 私有边界

# pub 关键字

pub修饰结构体使其公有，pub修饰字段使字段公有。

 ```rust
 mod back_of_house {
     pub struct Breakfast { // 公共结构体
         pub toast: String, // 公共字段
         seasonal_fruit: String,
     }
     
     impl Breakfast {
         pub fn summer(toast:&str) -> Breakfast {
             Breakfast {
                 toast: String::from(toast),
                 seasonal_fruit: String::from("peaches"),
             }
         }
     }
 }
 
 pub fn eat_at_restaurant() {
     let mut meal = back_of_house::Breakfast::summer("Rye");
     meal.toast = String::from("Wheat");
     println!("I'd like {} toast please", meal.toast);
     meal.seasonal_fruit = String::from("blueberries"); // 编译不通过，因为seasonal_fruit是私有字段
 }
 ```

pub修饰enum，enum和变体都是公共的了:

```rust
mod back_of_house {
    pub enum Appetizer {
        Soup,
        Salad,
    }
}
```

# use 关键字

类似于python中的`import`关键字。

# as 关键字

类似于python中的`as`关键字

# 使用外部包

# 向量 Vector

Vector在堆上是连续的，只能存放同类型的数据，大小动态。

例子：

```rust
fn main() {
    let v: Vec<i32> = Vec::new();
}
```

更常见的创建方式，使用宏`vec!`来创建：

```rust
fn main() {
    let v = vec![1, 2, 3]; // rust可以自动推断出这个vec中数据的类型是i32
}
```

**更新：**

```rust
fn main() {
    let mut v = Vec::new();
	v.push(1); // 如果使用了push(1)，rust就可以推断出上面的v是什么类型了
}
```

**删除：**

按照所有权规则，走出作用域则被删除。

**读取：**

使用索引读取：

```rust
fn main() {
    let v = vec![1, 2, 3, 4, 5];
    let third: &i32 = &v[2];
}
```

使用`get()`方法读取，返回值为Option<T>枚举，因此可以使用match模式匹配：

```rust
fn main() {
    let v = vec![1, 2, 3, 4, 5];
    let third: &i32 = &v[2];
	match v.get(2) {
        Some(third) => println!("The third element is {}", third),
        None => println!("There is no third element"),
    }
}
```

索引读取的时候数组越界的话会panic。

**遍历：**

for 循环遍历：

```rust
fn main() {
    let v = vec![1, 2, 3, 4, 5];
    for i in &v {
        println!("{}", i); // 这里打印了1 2 3 4 5，而不是地址，是因为println!宏实现了Display trait所以编译器自动解引用了i的实际值进行打印
    }
}
```



**vector + enum案例:**

```rust
enum SpreadsheetCell {
    Int(i32),
    Float(f64),
    Text(String),
}

fn main() {
	let row = vec![
        SpreadsheetCell::Int(3),
        SpreadsheetCell::Text(String::from("blue")),
        SpreadsheetCell::Float(10.12), 
    ]
}
```



# String

字符串是byte集合。



**创建：**

创建一个空字符串`String::new();`

从字符串字面值创建字符串：

```rust
fn main() {
    let data = "initial contents";
    let s = data.to_string();
    
    let s1 = "initial contents".to_string();
    
    let s2 = String::from("initial contents");
}
```

 

**更新：**

`push_str()`方法的入参要求是字符串切片。

 ```rust
 fn main() {
     let mut s = String::from("foo");
 
     s.push_str("bar"); //传的是字符串切片，"bar"作为字符串字面值就是一种字符串切片
 
     println!("{}", s);  // 输出结果 foobar
 }
 ```

对于这种情况，入参是字符串引用：

```rust
fn main() {
    let mut s = String::from("foo");

    let s1 = String::from("bar");

    s.push_str(&s1);

    println!("{}", s); 
}
```

为什么这样可以编译通过？

> 为什么可以将 `String` 类型的引用作为参数传递给期望字符串切片（`&str`）的函数。这里的关键是 Rust 的自动解引用（deref）特性和解引用强制多态（Deref coercion）。
>
> 当你尝试将 `String` 类型的引用传递给一个期望 `&str` 类型参数的函数时，Rust 会自动将 `String` 引用解引用为 `&str`。这一过程是通过 `Deref` trait 实现的，该 trait 为 Rust 的类型提供了一个将自身转换为引用的另一种类型的能力。`String` 类型实现了 `Deref` trait，其 `deref` 方法会返回字符串数据的切片 `&str`。
>
> ### 解引用强制多态（Deref Coercion）
>
> 解引用强制多态是 Rust 的一个便利特性，它允许我们在某些情况下自动将引用转换为另一种类型的引用。具体来说，当你传递 `&String` 给一个期望 `&str` 的地方时，Rust 在幕后自动使用 `Deref` trait 将 `&String` 转换为 `&str`，因为 `String` 可以被解引用成 `str`。
>
> ### 示例
>
> 假设有一个函数 `push_str`，它接受一个 `&str` 类型的参数：
>
> ```rust
> fn example_push_str(s: &str) {
>     // 实现细节...
> }
> ```
>
> 你可以用 `String` 类型的引用作为参数调用它，即使 `example_push_str` 期望的是 `&str`：
>
> ```rust
> let s = String::from("foo");
> example_push_str(&s); // 自动解引用 &String 到 &str
> ```
>
> 在这个例子中，`&s` 是 `&String` 类型，但由于 `Deref` 强制多态，Rust 编译器自动将其转换为 `&str`，从而满足 `example_push_str` 函数的参数类型要求。
>
> ### 总结
>
> 总之，即使 `push_str` 的入参是字符串切片 `&str`，你也可以传递 `String` 类型的引用，因为 Rust 的解引用强制多态机制会自动将 `String` 类型的引用转换为字符串切片。这种设计提高了 Rust 代码的灵活性和易用性，允许 `String` 和 `&str` 在很多上下文中无缝互操作。



`push`可以将单个字符附加到字符串上。



`+`拼接字符串：

```rust
fn main() {
    let s1 = String::from("Hello, ");
    let s2 = String::from("World!");
    
    let s3 = s1 + &s2; // 使用了类似fn add(self, s: &str) -> String的方法
    println!("{}", s3);
    println!("{}", s1); // 编译不通过，s1失效了，因为所有权转移到了add函数的第一个参数变量上了
    println!("{}", s2); 
}
```



`format!`宏来拼接：

```rust
fn main() {
    let s1 = String::from("tic");
    let s2 = String::from("tac");
    let s3 = String::from("toe");
    
    let s = format!("{} - {} - {}", s1, s2, s3);
    println!("{}" , s);
}
```



**遍历：**



# HashMap

**创建：**

```rust
use std::collections::HashMap

fn main() {
    let mut scores: HashMap<String, i32> = HashMap::new();
    scores.insert(String::from("Blue"), 10);  // 添加
}
```



 使用`collect()`创建：

```rust
use std::collections::HashMap;

fn main() {
    let teams = vec![String::from("Blue"), String::from("Yellow")];
    let intial_scores = vec![10, 50];
    
    let scores: HashMap<_, _> = teams.iter().zip(intial_scores.iter()).collect();
}
```



访问：

使用`get()`方法，参数是key，返回值是Option枚举。

```rust
use std::collections::HashMap;

fn main() {
    let mut scores = HashMap::new();
    
    scores.insert(String::from("Blue"), 10);
    scores.insert(String::from("Yellow"), 50);
    
    let team_name = String::from("Blue");
    let score = scores.get(&team_name);
    
    match score {
        Some(s) => println!("{}", s),
        None => println!("team not exist"),
    }
}
```



遍历：

```rust
use std::collections::HashMap;

fn main() {
    let mut scores = HashMap::new();
    
    scores.insert(String::from("Blue"), 10);
    scores.insert(String::from("Yellow"), 50);
    
    for (k, v) in &scores {
        println!("{}: {}", k, v);
    }
}
```

 

更新：

判断是否存在某个key，然后再插入，要借助Entry enum：

```rust
use std::collections::HashMap;

fn main() {
    let mut scores = HashMap::new();
   	
    scores.insert(String::from("Blue"), 10);
    scores.entry(String::from("Blue")).or_insert(50);
    
}
```

例子：

```rust
use std::collections::HashMap;

fn main() {
    let text = "hello world hello hammer"
    let mut word_counter = HashMap::new();
    
    for word in text.split_whitespace() {
        let count = word_counter.entry(word).or_insert(0);
        *count += 1;
    }
    
    println!("{:#?}", map)
}
```

# Panic

panic可以选择中止或展开，默认展开模式。

在展开的模式下，rust会在程序panic时，反向清理调用栈中的数据（工作量很大），如果是中止模式，则程序直接停止，所有内存数据由OS处理。

中止模式，需要修改`Cargo.toml`文件：
```toml
...
[profile.release]
panic = 'abort'
```



panic宏例子：

```rust
fn main() {
    // panic!("crash and burn");
	let v = vec![1, 2, 3]
    v[99];
}
```

设置环境变量`RUST_BACKTRACE=1`则可以得到panic!宏的回溯信息。

当我们在执行`cargo run`这个命令的时候，默认就是带了调试信息的，除非我们加上`--release`。

 

# Result 枚举

例子：

```rust
use std::fs::File;

fn main() {
    let f = File::open("hello.txt");
    
    let f = match f {
        Ok(file) => file,
        Err(error) => {
            panic!("Error opening file {:?}", error)
        }
    };
}
```

进一步匹配不同的错误：

```rust
use std::fs::File;
use std::io::ErrorKind;

fn main() {
    let f = File::open("hello.txt");
    
    let f = match f {
        Ok(file) => file,
        Err(error) => match error.kind() {
             ErrorKind::NotFound => match File::create("hello.txt") {
                 Ok(fc) => fc,
                 Err(e) => panic!("Error creating file: {:?}", e),
            },
            other_error => panic!("Error opening the file: {:?}", other_error),
        }, 
    };
}
```

使用闭包来简化代码：

```rust
use std::fs::File;
use std::io::ErrorKind;

fn main() {
    let f = File::open("hello.txt").unwarp_or_else(|error| {
        if error.kind() == ErrorKind::NotFound {
            File::create("hello.txt").unwarp_or_else(|error| {
                panic!("Error creating file: {:?}", error);
            })
        } else {
            panic!("Error opening the file: {:?}", error);
        }
    });
}    
```



`unwrap()`方法，如果Result的结果是Ok，则返回Ok里面的值，如果是Err则调用panic!宏：

```rust
use std::fs::File;

fn main() {
    // let f = File::open("hello.txt");
    
    // let f = match f {
        // Ok(file) => file,
        // Err(error) => {
            // panic!("Error opening file {:?}", error)
        // }
    // };
    
    let f = File::open("hello.txt").unwarp(); // 等价于上面这段注释的代码
}
```



`expect()`方法，和`unwrap()`方法类似，但可以指定错误信息：

```rust
use std::fs::File;

fn main() {
    let f = File::open("hello.txt").expect("Failed to open the file");
}
```



传播错误：

```rust
use std::fs::File;
use std::io::{self, Read};

fn read_username_from_file() -> Result<String, io::Error> {
    // 打开文件，f是`Result<文件句柄,io::Error>`
    let f = File::open("hello.txt");

    let mut f = match f {
        // 打开文件成功，将file句柄赋值给f
        Ok(file) => file,
        // 打开文件失败，将错误返回(向上传播)
        Err(e) => return Err(e),
    };
    // 创建动态字符串s
    let mut s = String::new();
    // 从f文件句柄读取数据并写入s中
    match f.read_to_string(&mut s) {
        // 读取成功，返回Ok封装的字符串
        Ok(_) => Ok(s),
        // 将错误向上传播
        Err(e) => Err(e),
    }
}
```



使用`?`宏改写上面的代码：

```rust
use std::fs::File;
use std::io;
use std::io::Read;

fn read_username_from_file() -> Result<String, io::Error> {
    let mut f = File::open("hello.txt")?; // 如果打开文件失败则返回Err，并且会将错误隐式转换成函数返回值中的错误类型，如果成功则将结果赋值给f
    let mut s = String::new();
    f.read_to_string(&mut s)?;
    Ok(s)
}
```

`?`宏也可以链式调用：

```rust
use std::fs::File;
use std::io;
use std::io::Read;

fn read_username_from_file() -> Result<String, io::Error> {
    let mut s = String::new();
    File::open("hello.txt")?.read_to_string(&mut s)?;
    Ok(s)
}
```



# 泛型

泛型声明：

```rust
fn largest<T>(list: &[T]) -> T 
```



结构体中使用泛型：

```rust
struct Point<T> {
    x: T,
    y: T,
}

fn main() {
    let integer = Point { x: 5, y: 10 };
    let float = Point { x: 1.0, y: 4.0 };
}
```

使用不同的泛型：

```rust
struct Point<T,U> {
    x: T,
    y: U,
}

fn main() {
    let p = Point{x: 1, y :1.1};
}
```



枚举中使用泛型：

卧龙：

```rust
enum Option<T> {
    Some(T),
    None,
}
```

凤雏：

```rust
enum Result<T, E> {
    Ok(T),
    Err(E),
}
```



方法中的使用泛型：

```rust
struct Point<T, U> {
    x: T,
    y: U,
}

impl<T, U> Point<T, U> {
    fn mixup<V, W>(self, other: Point<V, W>) -> Point<T, W> {
        Point {
            x: self.x,
            y: other.y,
        }
    }
}

fn main() {
    let p1 = Point { x: 5, y: 10.4 };
    let p2 = Point { x: "Hello", y: 'c'};

    let p3 = p1.mixup(p2);

    println!("p3.x = {}, p3.y = {}", p3.x, p3.y);
}
```



为具体的泛型类型实现方法

```rust
impl Point<f32> {
    fn distance_from_origin(&self) -> f32 {
        (self.x.powi(2) + self.y.powi(2)).sqrt()
    }
}
```



# 单态化

Rust执行泛型代码的速度和执行具体类型代码的速度是一致的，因为Rust在编译时会将泛型替换成具体的类型，这一过程称为单态化。



# 特征（Trait）

trait的定义：

```rust
pub trait Summary {
    fn summarize(&self) -> String;
}
```

为类型实现trait:

```rust
// src/lib.rs
pub trait Summary {
    fn summarize(&self) -> String;
}
pub struct Post {
    pub title: String, // 标题
    pub author: String, // 作者
    pub content: String, // 内容
}

impl Summary for Post {
    fn summarize(&self) -> String {
        format!("文章{}, 作者是{}", self.title, self.author)
    }
}

pub struct Weibo {
    pub username: String,
    pub content: String
}

impl Summary for Weibo {
    fn summarize(&self) -> String {
        format!("{}发表了微博{}", self.username, self.content)
    }
}
```

在`main.rs`中调用，假设`Cargo.toml`中的package包名是demo：

```rust
use demo::Summary;
use demo::Weibo;
use demo::Post;

fn main() {
    let post = Post{title: "Rust语言简介".to_string(),author: "Sunface".to_string(), content: "Rust棒极了!".to_string()};
    let weibo = Weibo{username: "sunface".to_string(),content: "好像微博没Tweet好用".to_string()};

    println!("{}",post.summarize());
    println!("{}",weibo.summarize());
}
```

# 特征对象



# 对象安全



# 孤儿规则



# 闭包

闭包的意义在于代码解耦合，可维护。

每个闭包表达式具有唯一的匿名类型。

闭包捕获变量有三种途径，恰好对应闭包函数参数的三种传入方式：转移所有权、可变借用、不可变借用，因此相应的 `Fn` 特征也有三种：

1. `FnOnce`，该类型的闭包会拿走被捕获变量的所有权。运行环境中的变量所有权被转移到闭包中了，那必然意味着这个闭包下次再也不能从运行环境中拿到这个已经被转移了所有权的变量的所有权了，所以`FnOnce`类型的闭包**只能运行一次**。但是如果该变量类型实现了Copy Trait，那闭包每次获取该变量所有权时获取的都是该变量的副本的所有权，所以即使是`FnOnce`类型的闭包**也有可能被多次运行**。如果想强制闭包取得捕获变量的所有权而非副本的所有权，可以在参数列表前添加 `move` 关键字，这种用法通常用于闭包的生命周期大于捕获变量的生命周期时，例如将闭包返回或移入其他线程。
2. `FnMut`，它以可变借用的方式捕获了环境中的值，因此可以修改该值。
3. `Fn` 特征，它以不可变借用的方式捕获环境中的值

**一个闭包实现了哪种`Fn`特征，既取决于该闭包如何捕获变量，也取决于闭包体内如何使用这些被捕获的变量。**

实际上，一个闭包并不仅仅实现某一种 `Fn` 特征，规则如下：

- 所有的闭包都自动实现了 `FnOnce` 特征，因此任何一个闭包都至少可以被调用一次
- 没有移出所捕获变量的所有权的闭包自动实现了 `FnMut` 特征
- 不需要对捕获变量进行改变的闭包自动实现了 `Fn` 特征

# 迭代器

```rust
fn main() {
    let v1 = vec![1, 2, 3];
    let v1_iter = v1.iter();
    for val in v1_iter {
        println!("Got: {}", val);
    }
}
```



iterator trait:

```rust
pub trait Iterator {
    type Item;
    fn next(&mut self) -> Option<Self::Item>;
    // ...
}
```

例子：

```rust
#[cfg(test)]
mod tests {
	#[test]
    fn iterator_demonstration() {
    	let v1 = vec![1, 2, 3];
    	let mut v1_iter = v1.iter(); // mut可变是因为next()方法会修改迭代器的某个字段值，所以这里必须用mut
    
    	assert_eq!(v1_iter.next(), Some(&1));
    	assert_eq!(v1_iter.next(), Some(&2));
    	assert_eq!(v1_iter.next(), Some(&3));
	}
}
```

![image-20240211190514994](/home/lilhammer/snap/typora/86/.config/Typora/typora-user-images/image-20240211190514994.png)



消耗迭代器的方法：

 `sum()`方法：

```rust
fn iterator_sum() {
    let v1 = vec![1, 2, 3];
    let v1_iter = v1.iter();
    
    let total: i32 = v1_iter.sum();
    println!("total: {}", total);
}
```

`map()`方法，接受一个闭包，闭包作用于每个元素：

```rust
fn iterator_map() {
    let v1 = vec![1, 2, 3];
    let v2: Vec<_> =  v1.iter().map(|x| x + 1).collect(); // collect()方法会消耗这个map()迭代器适配器
}
```

`filter()`方法，接受一个闭包，在遍历时会进行判断，如果为true则元素将会被包含在filter产生的迭代器中：

```rust
struct Shoe {
    size: u32,
    style: String,
}

fn shoes_in_size(shoes: Vec<Shoe>, shoe_size: u32) -> Vec<Shoe> {
    shoes.into_iter().filter(|s| s.size == shoe_size).collect()
}

```



使用Iterator trait创建自定义迭代器：

```rust
struct Counter {
    count: u32,
}

impl Counter {
    fn new() -> Counter {
        Counter { count: 0 }
    }
}

impl Iterator for Counter {
    type Item = u32;

    fn next(&mut self) -> Option<Self::Item> {
        if self.count < 5 {
            self.count += 1;
            Some(self.count)
        } else {
            None
        }
    }
}

#[test]
let sum: u32 = Counter::new()
    .zip(Counter::new().skip(1))
    .map(|(a, b)| a * b)
    .filter(|x| x % 3 == 0)
    .sum();
assert_eq!(18, sum);

```

 

# release profile



# 文档注释



# Workspace

```toml
[workspace]
members = [
	"adder",
	"add-one",
	"add-two",
]
```



# 智能指针



# Deref Trait



# Drop Trait

drop trait在prelude中。

# Rc\<T>

# 内部可变性

无法可变地借用一个不可变的值：

```rust
fn main() {
    let x = 5;
    let y = &mut x; // x是不可变的，&mut x就是可变地借用不可变的值，所以编译不通过
}
```



# RefCell\<T>



# 并发

# thread::Spawn

# Channel



# OOP



# 静态分派

```rust
trait Speak {
    fn speak(&self);
}

struct Dog;
struct Cat;

impl Speak for Dog {
    fn speak(&self) {
        println!("Woof!");
    }
}

impl Speak for Cat {
    fn speak(&self) {
        println!("Meow!");
    }
}

fn make_some_noise<T: Speak>(animal: &T) {
    animal.speak();
}

fn main() {
    let dog = Dog;
    let cat = Cat;

    make_some_noise(&dog); // 在编译时确定调用 Dog::speak
    make_some_noise(&cat); // 在编译时确定调用 Cat::speak
}
```



# 动态分派

```rust
trait Speak {
    fn speak(&self);
}

struct Dog;
struct Cat;

impl Speak for Dog {
    fn speak(&self) {
        println!("Woof!");
    }
}

impl Speak for Cat {
    fn speak(&self) {
        println!("Meow!");
    }
}

fn make_some_noise(animal: &dyn Speak) {
    animal.speak();
}

fn main() {
    let dog = Dog;
    let cat = Cat;

    make_some_noise(&dog); // 使用动态分派调用 speak
    make_some_noise(&cat); // 使用动态分派调用 speak
}
```



# 类型擦除



# 状态模式（state pattern）



# 可辩驳的



# 模式

直接匹配字面值：



匹配命名变量：

```rust
let some_value = Some(5);

match some_value {
    Some(x) => println!("Got an integer: {}", x),
    None => println!("Got nothing"),
}
```

在这个例子中，`Some(x)`是一个模式，它匹配`some_value`中的`Some`变体。如果`some_value`是`Some`变体，那么它内部的值将被绑定到变量`x`上，并可以在相应的分支代码块中使用。这里的`x`就是一个命名变量，它允许我们在模式匹配的分支中访问匹配到的值。

命名变量在处理更复杂的数据结构时特别有用，例如结构体、枚举或嵌套的模式：

```rust
enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
}

let msg = Message::Move { x: 3, y: 4 };

match msg {
    Message::Quit => println!("Quit"),
    Message::Move { x, y } => println!("Move to x: {}, y: {}", x, y),
    Message::Write(text) => println!("Text message: {}", text),
}
```

在这个例子中，`Message::Move { x, y }`模式匹配`Message`枚举的`Move`变体，并将`Move`变体中的`x`和`y`字段绑定到同名的变量`x`和`y`上。这样我们就可以在打印语句中直接使用这些变量。

模式匹配中的变量绑定默认是不可变的。如果需要可变地绑定变量，可以使用`mut`关键字（例如`Some(mut x)`）。



多重模式：

使用`|`语法表示或，就是可以匹配多种模式。

```rust
fn main() {
    let x = 1;
    match x {
        1 |2 => println!("one or two"),
        _ => println!("others"),
    }
}
```



使用`..=`语法匹配范围：

```rust
fn main() {
    let x = 5;
    match x {
        1..=5 => println!("one through five"),
        _ => println!("something else"),
    }
}
```



下划线开始命名的变量即使后续没有使用，编译也不会警告：

```rust
fn main() {
    let _x = 5;
    let y = 10; 
}
```



使用`..`忽略不需要的部分：

```rust
fn main() {
    let numbers = (2, 4, 6, 8, 10);
    match numbers {
        (first, .., last) => {
            println!("some numbers: {}, {}", first, last);
        },
    }
    
    match numbers {
        (.., seconde, ..) => { // 编译不通过，因为有歧义
            println!("some numbers: {}", second) 
        },
    }
}
```



match守卫：

```rust
fn main() {
    let num = Some(4);
    match num {
        Some(x) if x < 5 => println!("less than five: {}", x), //这里的if x < 5就是match守卫
        None => (),
    }
}
```



`@`绑定，让我们可以创建一个变量，该变量可以在测试某个值是否与模式匹配的同时保存该值：

```rust
enum Message {
    Hello { id: i32 },
}

let msg = Message::Hello { id: 5 };

match msg {
    Message::Hello { id: id_variable @ 3..=7 } => {
        println!("Found an id in range: {}", id_variable)
    },
    Message::Hello { id: 10..=12 } => {
        println!("Found an id in another range")
    },
    Message::Hello { id } => {
        println!("Found some other id: {}", id)
    },
}
```



# Unsafe Rust



# 函数指针

当把函数作为参数传递给函数的时候，函数会被强制转换成fn类型，也即函数指针（function pointer ）。



































































































































