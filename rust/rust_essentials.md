# 命名规范

rust使用snake case命名规范，所有字母小写，常量所有字母大写。

# mut

使用`mut`关键字声明的变量才可变

```rust
let mut x = 1;
```

# const

例子：`const PI:f64 = 3.14;`

常量的类型必须标注。

常量当然不可以使用`mut`关键字

# shadowing

shadowing 可以解决变量类型转换时重新命名的问题，比如原先的age_str要转成int类型需要额外使用一个变量age_int来接受，但是rust的shadowing特性可以解决。

使用方法很简单就是使用let命名同名变量：

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

tuple可以解构。

```rust
let (x, y, z) = tup;
println!("{} {} {}", x, y, z);
```

# 数组

类型固定，长度固定。

声明方式，方式一：

```rust
let a = [1, 2, 3, 4, 5]; 
```

声明方式二：

```rust
let a = [3;5]; // equal to let a = [3, 3, 3, 3, 3];
```

数组保存在stack上而不是heap上。 

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
        x + 3 // 注意这里没有分号
    }
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

1. 函数返回值声明方式：`-> i32`

例如：

```rust
fn plus_five(x: i32) -> i32 {
    x + 5
}
```

` x + 5`后面不能带分号，也即不能是这样： `x + 5;`，因为这样就是一个语句statement而不是expression表达式，语句的返回值类型是`tuple `。

2. 函数的返回值必须是一个`expression`，例如上面的

# 文档注释

# if expression

`if`的condition条件必须是`bool`类型。

# match

# loop

# 所有权

drop函数：

 clone函数：

copy函数：

# 引用 

类似于传递指针，但是传递引用给函数，所有权并不会转移给函数。

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

两个限制：

1. 不可以同时存在两个可变引用（并发安全）。
2. 不可以同时存在一个可变引用和一个不可变引用，因为不可变引用失去意义。

# Dangling Reference （悬空引用）

悬空引用是指指针所指向的数据被销毁，但是指针依然存在。

`rust`在编译阶段就禁止了悬空引用的发生。

# Slice

slice不持有所有权。

# 字符串切片

形式： [start_index .. end_index]，左包含，右不包含。

注意：字符串切片的范围索引必须发生在有效的UTF-8字符边界内。如果尝试从一个多字节的字符中创建字符串切片，程序会报错。

字符串字面值的类型就是字符串切片&str。

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

必须全量赋值，否则编译器报错。

访问方式为点标记法。

想要修改struct中的字段必须在实例化的时候使用`mut`修饰。

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

struct更新语法：

当想基于已存在的结构体实例创建新实例的时候，比如下面这种情况，其中`email`和`username`是新值，而`active`和`sign_in_count`的值来自user1：

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

没有任何字段的结构体。  

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



