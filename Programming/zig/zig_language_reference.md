### Container level variables

容器级别变量（我自己瞎翻译的），就是指具有静态生命周期(static lifetime)，延迟初始化(lazily analyzed)，并且这些变量的初始化不依赖于它们在代码中的顺序(order-independent)。

> 这些变量的初始化不依赖于它们在代码中的顺序，是指即使在代码顺序上，x还未“被初始化”，但是也可以先被使用，只要x是一个Container level variables，见下例。

```zig
var y: i32 = add(10, x);  // 在顺序上x还未初始化就被使用了，但这并不会报错，因为x是一个容器级别变量
const x: i32 = add(12, 34);

test "container level variables" {
    try expect(x == 46);
    try expect(y == 56);
}

fn add(a: i32, b: i32) i32 {
    return a + b;
}

const std = @import("std");
const expect = std.testing.expect;
```

不难猜到，所谓容器级别变量就是定义在最外部作用域（相对一个.zig文件而言），比如这里的x和y。还有add， expect等变量，你会发现他们都是在被定义之前就被调用了。

### Thread Local Variable

线程局部变量（翻译参考网络），顾名思义，这种变量在线程间独立，不被不同线程共享。

使用方式是使用`threadlocal`关键字修饰。

```zig
const std = @import("std");
const assert = std.debug.assert;

threadlocal var x: i32 = 1234;

test "thread local storage" {
    const thread1 = try std.Thread.spawn(.{}, testTls, .{});
    const thread2 = try std.Thread.spawn(.{}, testTls, .{});
    testTls();
    thread1.join();
    thread2.join();
}

fn testTls() void {
    assert(x == 1234);
    x += 1;
    assert(x == 1235);
}
```

### Local Variables

局部变量，看一下zig原文：

> Local variables occur inside [Functions](https://ziglang.org/documentation/master/#Functions), [comptime](https://ziglang.org/documentation/master/#comptime) blocks, and [@cImport](https://ziglang.org/documentation/master/#cImport) blocks.

我们可以使用`comptime`关键字来修饰一个变量，让他尽可能在编译器就已知了。

有个小知识是`const`修饰的变量不等于comptime-known，例如，从文件或用户输入中读取的数据可以赋给一个 `const` 变量，但这个过程必须在运行时进行。

使用`comptime`的好处和坏处：

好处：

1. **编译时常量**： 当你需要定义在编译时就已知且不会改变的值时，`comptime` 是非常适用的。这可以帮助编译器优化代码，减少运行时的负担。

2. **条件编译**： `comptime` 常用于条件编译，比如基于不同的编译配置或平台来启用或禁用代码段。

3. **模板和泛型编程**： 在使用泛型或模板编程时，`comptime` 可用于确定某些类型或参数，从而允许编译器在编译时就生成具体的实现。

4. **编译时计算**： 如果某个计算可以在编译时完成，而不是在运行时，使用 `comptime` 可以减少应用程序的运行时开销。

坏处：

1. **运行时数据**： `comptime` 变量的值必须在编译时已知。这意味着任何需要在运行时才能确定的数据，如用户输入、文件内容、网络数据等，都不能使用 `comptime` 修饰。如果一个程序的大部分功能依赖于运行时数据，那么 `comptime` 的使用就会非常有限。

2. **资源消耗**： 编译时计算虽然可以减少运行时的开销，但它会增加编译时间和编译器的资源消耗。对于大型项目或复杂的计算，过度使用 `comptime` 可能导致编译过程显著变慢。

3. **灵活性限制**： `comptime` 修饰的代码在编译时就已经固定，这限制了程序的灵活性。例如，配置项和行为的调整若依赖于 `comptime` 计算，那么每次更改都需要重新编译整个程序，这不利于快速迭代和部署。

4. **复杂性**： 过度使用 `comptime` 可能会使程序逻辑变得更复杂和难以理解。特别是在涉及多层 `comptime` 逻辑或条件编译的代码中，代码的维护和调试可能会变得更加困难。

5. **适用性**： 不是所有的编程问题都适合在编译时解决。有些问题在运行时解决更为合理，尤其是那些依赖于动态环境或实时数据反馈的场景。



### String Literals

> String literals are constant single-item [Pointers](https://ziglang.org/documentation/master/#Pointers) to null-terminated byte arrays. The type of string literals encodes both the length, and the fact that they are null-terminated, and thus they can be [coerced](https://ziglang.org/documentation/master/#Type-Coercion) to both [Slices](https://ziglang.org/documentation/master/#Slices) and [Null-Terminated Pointers](https://ziglang.org/documentation/master/#Sentinel-Terminated-Pointers). Dereferencing string literals converts them to [Arrays](https://ziglang.org/documentation/master/#Arrays).



关于字符串和字符数组：

在 Zig 中，字符串通常通过一个以 null 结尾的字符数组表示，这种方式类似于 C 语言。这意味着字符串字面量在 Zig 中实际上是一个指向字符数组的指针，其中数组的末尾由一个 null 字符 (`\0`) 表示。这个 null 字符充当了哨兵（sentinel），帮助标识字符串的结束，从而让程序知道字符串在哪里结束。

字符串和哨兵数组的处理:

1. **字符串字面量**：
   - 当你定义一个字符串字面量，如 `const same_message = "hello";` 时，编译器会自动在字符串的末尾添加一个 null 字符 (`\0`)。这样，`same_message` 实际上是一个指向字符数组 `{'h', 'e', 'l', 'l', 'o', '\0'}` 的指针。
2. **使用字符串**：
   - 当你需要处理字符串时，比如传递给函数或从函数返回，Zig 提供了一些内置的字符串处理功能，这些功能默认处理以 null 结尾的字符串。这包括标准库中的字符串操作函数，如字符串比较、长度计算等。
3. **哨兵终止符**：
   - Zig 语言提供了一种哨兵终止符的概念，它不仅仅用于字符串，还可以用于其他类型的数组。这允许编译器和运行时检查数组访问的界限，增强了程序的安全性和可靠性。
4. **哨兵和数组类型**：
   - 在 Zig 中，你可以定义一个数组并显式指定哨兵值，这样编译器就可以在编译时和运行时利用这个哨兵值来进行边界检查。对于字符串，通常使用 `\0` 作为哨兵。

示例:

```
zigCopy codeconst std = @import("std");

pub fn main() void {
    const message = "hello"; // Zig 自动在 "hello" 后添加 '\0'
    const length = std.mem.len(u8, message); // 计算长度时不包含 '\0'
    std.debug.print("The length of '{}' is {}.\n", .{message, length});
}
```

在这个例子中，`std.mem.len` 函数计算 `message` 的长度，不计入终止的 null 字符，因为它知道字符串以 `\0` 结尾。

因此，对于你的问题，是的，字符串在 Zig 中通常由指向以 null 字符终止的数组的单个指针表示，这个 null 字符就是哨兵，标识字符串的结束。这样的设计使字符串的处理既高效又安全。



### Integer Literals

整型字面量，直接看例子：
```zig
const decimal_int = 98222;
const hex_int = 0xff;
const another_hex_int = 0xFF;
const octal_int = 0o755;
const binary_int = 0b11110000;

// underscores may be placed between two digits as a visual separator
const one_billion = 1_000_000_000;
const binary_mask = 0b1_1111_1111;
const permissions = 0o7_5_5;
const big_address = 0xFF80_0000_0000_0000;
```

### Runtime Integer Values

当整型值不是编译时可知的，那可能会发生整型溢出(integer overflow)和除零错误，`+`或者`-`等操作符会导致整型溢出，所以zig提供了环绕算法和饱和算法操作符。

使用`+%`和`-%`包裹算术运算符会进行环绕计算，例如，在使用 8 位整数时，如果你有 `255 +% 1`，结果将是 `0`，而不是溢出。

使用`+|` 和 `-|`会进行饱和算法，例如，使用 `+|` 运算符，`255 +| 1` 在 8 位整数中将得到 `255` 而不是溢出到 `0`。

### Floats

直接看zig原文：

> Zig has the following floating point types:
>
> - `f16` - IEEE-754-2008 binary16
> - `f32` - IEEE-754-2008 binary32
> - `f64` - IEEE-754-2008 binary64
> - `f80` - IEEE-754-2008 80-bit extended precision
> - `f128` - IEEE-754-2008 binary128
> - `c_longdouble` - matches `long double` for the target C ABI

浮点型字面量：
```zig
const floating_point = 123.0E+77;
const another_float = 123.0;
const yet_another = 123.0e+77;

const hex_floating_point = 0x103.70p-5;
const another_hex_float = 0x103.70;
const yet_another_hex_float = 0x103.70P-5;

// underscores may be placed between two digits as a visual separator
const lightspeed = 299_792_458.000_000;
const nanosecond = 0.000_000_001;
const more_hex = 0x1234_5678.9ABC_CDEFp-10;
```

Nan，正无穷，负无穷：

> 小插曲：
>
> There is no syntax for NaN, infinity, or negative infinity. For these special values, one must use the standard library:
>
> 这是zig原文的表述 ，注意到它使用one must use ...的表述，这里one must use，可以理解为 you must use ...或者we must use ...，使用“one must”而不是“we must”确实体现了英语中的一种风格选择，它更正式、更中立，常用于书面语或正式场合。这种用法可以使指导或规则听起来更加客观和普遍适用。

```zig
const std = @import("std");

const inf = std.math.inf(f32);
const negative_inf = -std.math.inf(f64);
const nan = std.math.nan(f128);
```

### Floating Point Operations

浮点数运算。

我们摘抄一段zig原文并看看chatgpt如何解释。

原文：

### [Floating Point Operations](https://ziglang.org/documentation/master/#toc-Floating-Point-Operations) 

By default floating point operations use `Strict` mode, but you can switch to `Optimized` mode on a per-block basis:

float_mode_obj.zig

```
const std = @import("std");
const big = @as(f64, 1 << 40);

export fn foo_strict(x: f64) f64 {
    return x + big - big;
}

export fn foo_optimized(x: f64) f64 {
    @setFloatMode(.optimized);
    return x + big - big;
}
```

Shell

```
$ zig build-obj float_mode_obj.zig -O ReleaseFast
```

For this test we have to separate code into two object files - otherwise the optimizer figures out all the values at compile-time, which operates in strict mode.

float_mode_exe.zig

```
const print = @import("std").debug.print;

extern fn foo_strict(x: f64) f64;
extern fn foo_optimized(x: f64) f64;

pub fn main() void {
    const x = 0.001;
    print("optimized = {}\n", .{foo_optimized(x)});
    print("strict = {}\n", .{foo_strict(x)});
}
```

> gpt: 
>
> 这段代码和描述涉及到了在编程中处理浮点数运算的两种模式：严格模式（Strict mode）和优化模式（Optimized mode）。这在许多编程语言和编译器中是常见的概念，尤其是在处理需要精确数学计算的应用时非常重要。
>
> ### 浮点数运算模式
>
> 1. **严格模式（Strict Mode）**：
>    - 在严格模式下，浮点数运算遵循精确的数学规则和浮点数标准（如 IEEE 754）。这种模式保证了运算的精度和可预测性，但可能牺牲了一些性能。
> 2. **优化模式（Optimized Mode）**：
>    - 优化模式允许编译器进行一些优化，这些优化可能会改变运算的精度或结果。优化的目的是提高性能，尤其是在不需要严格精确结果的计算中。优化可能包括重新排序操作、减少某些运算的次数等。
>
> ### 代码描述的问题
>
> 代码示例展示了如何在 Zig 语言中切换这两种模式，并说明了为什么可能需要将代码分开编译到不同的对象文件中以避免编译器优化影响结果。
>
> - **函数 `foo_strict`**：
>   - 在默认的严格模式下运行，确保 `x + big - big` 的计算遵循精确的浮点数规则。
> - **函数 `foo_optimized`**：
>   - 切换到优化模式，这可能会导致计算 `x + big - big` 时产生不同的结果，因为编译器可能采用不同的优化策略，例如消除看似无用的加减操作。
>
> ### 实际应用
>
> 示例中，通过编译并运行这两个函数，可以观察到在不同模式下浮点数运算可能产生的不同结果。这对于软件开发中需要处理高精度计算的应用（如科学计算、金融分析等）尤其重要。开发者需要根据具体需求选择合适的模式，以平衡计算的精度和程序的性能。

通过一下命令编译目标文件和可执行文件：

```bsh
zig build-obj float_mode_obj.zig -O ReleaseFast
```

```bash
zig build-exe float_mode_exe.zig float_mode_obj.o -O ReleaseFast
```

输出结果：
```
(base) ~/test/test-zig
./float_mode_exe
optimized = 1e-3
strict = 9.765625e-4
```

### Operators

zig没有操作符重载(operator overloading)的特性，你看到的就是你看到的。

具体操作符可以参考这个链接：[Operators](https://ziglang.org/documentation/master/#toc-Operators) [§](https://ziglang.org/documentation/master/#Operators)

但是有必要暂时拿几个出来讲一讲：

解引用操作符`.*`:

```zig
	
const x: u32 = 1234;
const ptr = &x;
ptr.* == 1234
```

Unwrap Option操作符`.?`：

```zig
const value: ?u32 = 5678;  // value是一个可选类型
value.? == 5678  // 通过.?操作符unwrap出可选类型包裹的值5678
```

Defaulting Error Unwrap `a catch b`，`a catch |err| b`，`a`必须是一个`Error Unions`类型，这个还不太懂。。。

```zig
const value: anyerror!u32 = error.Broken;
const unwrapped = value catch 1234;
unwrapped == 1234
```

Null Check，null是等于null的，因为有可选类型哈哈哈哈：

```zig
const value: ?u32 = null;
(value == null) == true
```

### Arrays

> 我的思考：
>
> 数组虽然在代码语义上有长度所言，比如zig语言定义的const alt_message: [5]u8 = .{ 'h', 'e', 'l', 'l', 'o' };但是在底层并没有物理载体上的长度这一概念，所以讲白了，源代码中对数组进行取索引或者取切片，其实只是在对一个已知数组头元素的内存地址的连续内存空间进行操作，而操作系统底层并不保证程序的这种操作是不会出错的，但是形如高级语言zig，他又想为降低这个错误发生的概率，因此他提供了在编译时进行简单地安全检查（诸如数组越界）以及在编译时生成“检查数组边界的运行时代码“的**额外努力**，但我们要从本质上理解，这些也只是编译器去做的额外的努力，而不是数组与生俱来就拥有的东西，反而在操作系统底层或者内存存储的角度，数组确实是一个完全不带有长度概念的连续内存空间，他就好像一个不需要对任何东西负责的孩子一般。
>
> 那为什么切片又具有了长度了呢？ 他是真的在底层有长度这个信息吗？ 那既然如此为什么不把数组也设计成切片呢？
>
> 切片本质上是一种高级的数据结构（结构体），它的设计目的是为了提供比纯数组**更灵活、更安全**的方式来处理**序列数据**。切片通常包括以下几个关键部分：
>
> 1. **指向数据的指针**：这允许切片引用数组的一个子序列，或者是整个数组。
> 2. **长度**：这表示切片当前包含的元素数量。
> 3. **容量**（在go等语言中）：这是切片底层分配的数组可以包含的最大元素数量，有助于管理动态增长。
>
> 我们明白一切都是有得有失的，不以代价为前提去讨论收益都是幼稚的。数组和切片也是如此，即使切片是一种**更安全和更灵活的**操作数组的方式，但是同时也意味着他需要更多的资源的消耗，牺牲了更多性能，因为每次操作切片时，都需要进行边界检查，这可能影响到程序的执行效率。
> 

数组类型，直接看示例：

```zig
const expect = @import("std").testing.expect;
const assert = @import("std").debug.assert;
const mem = @import("std").mem;

// array literal
const message = [_]u8{ 'h', 'e', 'l', 'l', 'o' };

// alternative initialization using result location
const alt_message: [5]u8 = .{ 'h', 'e', 'l', 'l', 'o' };

comptime {
    assert(mem.eql(u8, &message, &alt_message));
}

// get the size of an array
comptime {
    assert(message.len == 5);
}

// A string literal is a single-item pointer to an array.
const same_message = "hello";

comptime {
    assert(mem.eql(u8, &message, same_message));
}

test "iterate over an array" {
    var sum: usize = 0;
    for (message) |byte| {
        sum += byte;
    }
    try expect(sum == 'h' + 'e' + 'l' * 2 + 'o');
}

// modifiable array
var some_integers: [100]i32 = undefined;

test "modify an array" {
    for (&some_integers, 0..) |*item, i| {
        item.* = @intCast(i);
    }
    try expect(some_integers[10] == 10);
    try expect(some_integers[99] == 99);
}

// array concatenation works if the values are known
// at compile time
const part_one = [_]i32{ 1, 2, 3, 4 };
const part_two = [_]i32{ 5, 6, 7, 8 };
const all_of_it = part_one ++ part_two;
comptime {
    assert(mem.eql(i32, &all_of_it, &[_]i32{ 1, 2, 3, 4, 5, 6, 7, 8 }));
}

// remember that string literals are arrays
const hello = "hello";
const world = "world";
const hello_world = hello ++ " " ++ world;
comptime {
    assert(mem.eql(u8, hello_world, "hello world"));
}

// ** does repeating patterns
const pattern = "ab" ** 3;
comptime {
    assert(mem.eql(u8, pattern, "ababab"));
}

// initialize an array to zero
const all_zero = [_]u16{0} ** 10;

comptime {
    assert(all_zero.len == 10);
    assert(all_zero[5] == 0);
}

// use compile-time code to initialize an array
var fancy_array = init: {
    var initial_value: [10]Point = undefined;
    for (&initial_value, 0..) |*pt, i| {
        pt.* = Point{
            .x = @intCast(i),
            .y = @intCast(i * 2),
        };
    }
    break :init initial_value;
};
const Point = struct {
    x: i32,
    y: i32,
};

test "compile-time array initialization" {
    try expect(fancy_array[4].x == 4);
    try expect(fancy_array[4].y == 8);
}

// call a function to initialize an array
var more_points = [_]Point{makePoint(3)} ** 10;
fn makePoint(x: i32) Point {
    return Point{
        .x = x,
        .y = x * 2,
    };
}
test "array initialization with function calls" {
    try expect(more_points[4].x == 3);
    try expect(more_points[4].y == 6);
    try expect(more_points.len == 10);
}
```

数组指针的内存地址确实是数组第一个元素的内存地址：
```zig
const std = @import("std");
const expect = @import("std").testing.expect;

test "Is the memory address of an array pointer the memory address of the first element" {
    var arr: [5]i32 = [5]i32{1, 2, 3, 4, 5};
    const ptr_of_1th: *i32 = &arr[0]; // 单项指针指向数组的第一个元素
    const ptr_of_arr: *[5]i32 = &arr; // 单项指针指向数组

    try expect(@intFromPtr(ptr_of_1th) == @intFromPtr(ptr_of_arr));
}
```

output:

```
1/1 demo1.test.Is the memory address of an array pointer the memory address of the first element...OK
All 1 tests passed.
```





### Sentinel-Terminated Arrays

The syntax `[N:x]T` describes an array which has a sentinel element of value `x` at the index corresponding to the length `N`.，例如：

```zig
const std = @import("std");
const expect = std.testing.expect;

test "0-terminated sentinel array" {
    const array = [_:0]u8{ 1, 2, 3, 4 };

    try expect(@TypeOf(array) == [4:0]u8);
    try expect(array.len == 4);  // 哨兵数组的长度虽然为4
    try expect(array[4] == 0);  // 但是却可以取索引为长度值处的值
}

test "extra 0s in 0-terminated sentinel array" {
    // The sentinel value may appear earlier, but does not influence the compile-time 'len'.
    const array = [_:0]u8{ 1, 0, 0, 4 };

    try expect(@TypeOf(array) == [4:0]u8);
    try expect(array.len == 4);
    try expect(array[4] == 0);
}
```

### Vectors

A vector is a group of booleans, [Integers](https://ziglang.org/documentation/master/#Integers), [Floats](https://ziglang.org/documentation/master/#Floats), or [Pointers](https://ziglang.org/documentation/master/#Pointers) which are operated on in parallel, using **SIMD instructions** if possible. Vector types are created with the builtin function [@Vector](https://ziglang.org/documentation/master/#Vector).

标量和向量间是严禁运算的，但是zig提供了内置函数`@splat`方便的把标量转向量。

简单看一下数组的例子：

```zig
const std = @import("std");
const expectEqual = std.testing.expectEqual;

test "Basic vector usage" {
    // Vectors have a compile-time known length and base type.
    const a = @Vector(4, i32){ 1, 2, 3, 4 };
    const b = @Vector(4, i32){ 5, 6, 7, 8 };

    // Math operations take place element-wise.
    const c = a + b;

    // Individual vector elements can be accessed using array indexing syntax.
    try expectEqual(6, c[0]);
    try expectEqual(8, c[1]);
    try expectEqual(10, c[2]);
    try expectEqual(12, c[3]);
}

test "Conversion between vectors, arrays, and slices" {
    // Vectors and fixed-length arrays can be automatically assigned back and forth
    const arr1: [4]f32 = [_]f32{ 1.1, 3.2, 4.5, 5.6 };
    const vec: @Vector(4, f32) = arr1;
    const arr2: [4]f32 = vec;
    try expectEqual(arr1, arr2);

    // You can also assign from a slice with comptime-known length to a vector using .*
    const vec2: @Vector(2, f32) = arr1[1..3].*;

    const slice: []const f32 = &arr1;
    var offset: u32 = 1; // var to make it runtime-known
    _ = &offset; // suppress 'var is never mutated' error
    // To extract a comptime-known length from a runtime-known offset,
    // first extract a new slice from the starting offset, then an array of
    // comptime-known length
    const vec3: @Vector(2, f32) = slice[offset..][0..2].*;
    try expectEqual(slice[offset], vec2[0]);
    try expectEqual(slice[offset + 1], vec2[1]);
    try expectEqual(vec2, vec3);
}
```

### Pointers

指针，zig总共有两种指针，一个是单项指针(single-item pointer)，另一个是多项指针(many-item pointer)。

看一下他们的语法：

> - `*T` : single-item pointer to exactly one item.
>  - Supports deref syntax: `ptr.*`
>   - Supports slice syntax: `ptr[0..1]`
>   - Supports pointer subtraction: `ptr - ptr`
>   
>-  `[*]T` : many-item pointer to unknown number of items.
>   - Supports index syntax: `ptr[i]`
>  - Supports slice syntax: `ptr[start..end]` and `ptr[start..]`
>   - Supports pointer-integer arithmetic: `ptr + int`, `ptr - int`
>   - Supports pointer subtraction: `ptr - ptr`

注意到一个很神奇的地方，就是对单项指针取了0到1的索引！这会在需要切片类型的时候起到作用。



These types are closely related to [Arrays](https://ziglang.org/documentation/master/#Arrays) and [Slices](https://ziglang.org/documentation/master/#Slices):

- `*[N]T`: pointer to N items, same as single-item pointer to an array.
  - Supports index syntax: `array_ptr[i]`
  - Supports slice syntax: `array_ptr[start..end]`
  - Supports len property: `array_ptr.len`
  - Supports pointer subtraction: `array_ptr - array_ptr`



### Pointer Arithmetic

### Volatile

`@ptrCast` 的主要用途是在你知道某个内存位置实际上包含与当前指针类型不同的数据时，进行强制类型转换。例如，当你有一个指向字节数组的指针，但你知道这些字节实际上表示一个整数，你可以使用 `@ptrCast` 将指向字节数组的指针转换为指向整数的指针。

示例代码：
```zig
const std = @import("std");
const expect = std.testing.expect;

test "pointer casting" {
    const bytes align(@alignOf(u32)) = [_]u8{ 0x12, 0x12, 0x12, 0x12 };
    const u32_ptr: *const u32 = @ptrCast(&bytes);
    try expect(u32_ptr.* == 0x12121212);

    // Even this example is contrived - there are better ways to do the above than
    // pointer casting. For example, using a slice narrowing cast:
    const u32_value = std.mem.bytesAsSlice(u32, bytes[0..])[0];
    try expect(u32_value == 0x12121212);

    // And even another way, the most straightforward way to do it:
    try expect(@as(u32, @bitCast(bytes)) == 0x12121212);
}
```



### Allowzero

`allowzero` 属性是为了在特定环境下（如 freestanding 环境）处理特殊内存地址需求而设计的。

Zig 语言中的指针默认不允许地址为 0 的情况，以避免空指针错误。而`allowzero` 属性允许指针合法地指向地址 0，这在 freestanding 环境中非常重要，因为在这种情况下，地址 0 可能是有效的内存地址。

```zig
const std = @import("std");
const expect = std.testing.expect;

test "allowzero" {
    var zero: usize = 0; // var to make to runtime-known
    _ = &zero; // suppress 'var is never mutated' error
    const ptr: *allowzero i32 = @ptrFromInt(zero);  // 这里必须要使用allowzero关键字，如果没有allowzero，编译器会认为 ptr 指向地址 0 是无效的，并抛出错误。
    try expect(@intFromPtr(ptr) == 0);
}
```



### Alignment

> Each type has an **alignment** - a number of bytes such that, when a value of the type is loaded from or stored to memory, the memory address must be evenly divisible by this number. You can use [@alignOf](https://ziglang.org/documentation/master/#alignOf) to find out this value for any type.
>
> Alignment depends on the CPU architecture, but is always a power of two, and less than `1 << 29`.
>
> In Zig, a pointer type has an alignment value. If the value is equal to the alignment of the underlying type, it can be omitted from the type:

这是zig原文，其实就是想表达：

1. 当指针类型的对齐值与它所指向的类型的默认对齐值相同时，可以省略对齐值的显式指定，因为它们默认是相同的。

2. 可以显式指定指针类型的对齐值，以满足特定需求。

3. 非指针类型的对齐值是固定的，用户不能直接修改。

```zig
const std = @import("std");
const expect = std.testing.expect;

test "指针对齐值的省略与显式指定" {
    var x: i32 = 1234;
    // 省略对齐值，默认使用 *i32 的对齐值
    var default_ptr: *i32 = &x;
    try expect(@TypeOf(default_ptr) == *i32);
    try expect(@alignOf(@TypeOf(default_ptr)) == @alignOf(i32));

    // 显式指定对齐值为 8
    var custom_ptr: *align(8) i32 = &x;
    try expect(@TypeOf(custom_ptr) == *align(8) i32);
    try expect(@alignOf(@TypeOf(custom_ptr)) == 8);
    
    // 验证非指针类型的对齐值（用户无法直接指定）
    try expect(@alignOf(i32) == 4); // 假设在目标架构上 i32 的对齐值是 4
}
```



### Sentinel-Terminated Pointer

哨兵指针。



### Slice

>  **A slice is a pointer and a length.** The difference between an array and a slice is that the array's length is part of the type and known at compile-time, whereas the slice's length is known at runtime. Both can be accessed with the `len` field.

猜猜下面这个打印的结果是什么呢（当前版本：`0.14.0-dev.781+f03d54f06` ）：
```zig
const std = @import("std");

fn startIndex(n: i32) usize {
    const mod = @mod(n, 42);
    return @intCast(mod);
}

pub fn main() !void {
    const arr = [_]i32{ 1, 2, 3, 4 };
    const optimized_slice = arr[1..];
    const start_idx = startIndex(42);
    const slice = arr[start_idx..];
    std.debug.print("{}\n{}\n{}", .{@TypeOf(arr), @TypeOf(optimized_slice),@TypeOf(slice)});
}
```

output:

```
[4]i32
*const [3]i32
[]const i32
```

`optimized_slice`的类型竟然是*const [3]i32，因为当切片的索引是静态的，那编译器会为这个slice进行优化，他的类型就是指向子数组的一个指针。



### Sentinel-Terminated Slices

看这个例子就行啦

```
const std = @import("std");
const expect = std.testing.expect;

test "0-terminated slicing" {
    var array = [_]u8{ 3, 2, 1, 0, 3, 2, 1, 0 };
    var runtime_length: usize = 3;
    _ = &runtime_length;
    const slice = array[0..runtime_length :0];

    try expect(@TypeOf(slice) == [:0]u8);
    try expect(slice.len == 3);
    try expect(slice[3] == 0); // 可以取长度值索引
}

test "any-value-terminated slicing" {
    var array = [_]u8{ 3, 2, 1, 42, 3, 2, 1, 0 };
    var runtime_length: usize = 3;
    _ = &runtime_length;
    const slice = array[0..runtime_length :42];

    try expect(@TypeOf(slice) == [:42]u8);
    try expect(slice.len == 3);
    try expect(slice[3] == 42); // 可以取长度值索引
}
```