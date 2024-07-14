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

