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

gbi，就是指**为泛型实现trait。**

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



**GBI不能被重写呀！！！**

```rust
impl Even for u8 { // ❌
    fn is_even(self) -> bool {
        self % 2_u8 == 0_u8
    }
}
```



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
