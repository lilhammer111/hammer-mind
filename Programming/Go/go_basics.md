---
title: go 笔记
date: 2023-07-29 14:55:20
categories: ["programming", "go"]
tags: ["go"]
---



## go 编码规范

### 命名规范

#### 命名法概述

1. 驼峰命名法 CamelCase
2. 蛇形命名法 snake_case
3. 串式命名法 kebab-case



#### 包名

1. 小写
2. 简短
3. 不使用_
4. 不混合大小写

#### 文件命名

1. 小写
2. 遵循snake_case命名法

#### 结构体

1. 驼峰命名法
2. 首字母遵循go私有规则

#### 接口

1. 驼峰命名法
2. 只有一个待实现函数的时候，接口命名为该函数名+er， 如Reader接口只有Read方法待实现

#### 变量

1. CamelCase
2. 首字母遵循go私有规则
3. 组合简写词，如API，ID，URL，要么都大写，要么都小写

#### 常量

1. CamelCase

2. 首字母遵循go私有规则



### 注释规范

#### 代码注释

1. 单行注释 // 
2. 多行注释也使用 // 而不使用/* */

#### 包注释

```
// util包， 该包的介绍
// 创建人： xxx
// 创建时间： xxxx
```

#### 函数注释

#### 代码逻辑注释

#### 注释风格

### import规范

用空行隔开三类包：

1. std包
2. 第三方包
3. 自己的sdk

### 错误处理规范

1. 全部处理
2. 尽早return
3. 不要panic或者log.Fatal
4. 错误描述英文必小写，不写标点



## 环境安装

goland新建项目



## 常用命令

### go build

跨平台编译

```bash
env GOOS=linux GOARCH=amd64 go build
```

参数-n，并不实际编译，而是展示编译过程

参数-race，发现隐含的数据竞争问题，可能需要加锁，用法是，先使用go build -race xxx编译，然后再运行，运行时会资源竞争的错误

### go vet

go vet 是 Go 语言中的一个静态代码分析工具，用于检查代码中的常见错误和潜在问题。它可以帮助开发者发现一些常见的编码错误、代码规范问题和性能隐患。使用 go vet 工具可以增强代码的质量和可读性，提高软件的稳定性和效率。

以下是 go vet 工具的主要作用：

1. 静态分析：go vet 使用静态分析技术检查代码，而无需实际执行程序。它会检查代码中的潜在问题、不当使用的语法结构和常见错误。

2. 错误检查：go vet 可以检查出一些潜在的编码错误，例如未使用的变量、未初始化的变量、类型转换错误等。它还可以检查常见的逻辑错误，如条件判断和循环语句中的问题。

3. 规范检查：go vet 可以检查代码是否符合 Go 语言的规范和最佳实践。例如，它可以检查非法的导入路径格式、不正确的函数命名、不充分的错误处理等。

4. 性能优化：go vet 可以发现一些潜在的性能问题，如不必要的字符串拼接、低效的切片使用、不必要的类型转换等。通过修复这些问题，可以提高代码的性能和效率。

需要注意的是，go vet 并不能覆盖所有可能的问题，因此在代码审核和测试过程中，还应该结合其他工具和方法进行全面检查。另外，定期运行 go vet 工具可以及早发现问题，并改进代码质量。

### go install

与go build不同的是，这个是将编译后的输出文件打包成库放在pkg文件夹下

### go get

用于获取第三方包

-u参数，是指update,使用最新的包

### go fmt 

格式化代码

### go test

#### 概述

go test分为三种类型: 

- 测试函数,前缀为Test
- 基准函数,前缀为Benchmark
- 示例函数,前缀为Example

-v参数会将过程打印

测试文件名格式：xxx_test.go

xxx一般是所要测试代码的文件名，但不绝对，只是最佳实践。

案例:

```go 
// main_test.go
package main

import "testing"

func TestPrint1to20(t *testing.T) {
	t.SkipNow()
	res := Print1to20()
	if res != 211 {
		t.Errorf("calculation end is %v", res)
	}
}
```

TestMain()

```go
// main_test.go
package main

import (
	"fmt"
	"testing"
)

func testPrint(t *testing.T) {
	res := Print1to20()
	if res != 210 {
		t.Errorf("calculation end is %v", res)
	}
}

func testPrint2(t *testing.T) {
	res := Print1to20()
	res++
	if res != 211 {
		t.Errorf("test print2 faild")
	}
}

func TestAll(t *testing.T) {
	t.Run("testPrint", testPrint)
	t.Run("testPrint2", testPrint2)
}

func TestMain(m *testing.M) {
	fmt.Println("test begins...")
	m.Run()
}
```



#### 测试组

基础测试案例

```go
package split

import (
	"reflect"
	"testing"
)

func TestSplit(t *testing.T) {
	//got := Split("我爱爱你", "爱")
	//want := []string{"我", "你"}
	got := Split(":a:b::c:", ":")
	want := []string{"a", "b", "c"}
	if !reflect.DeepEqual(got, want) {
		t.Errorf("\nSplit failed!\nwant: %v,\ngot:%v,\n", want, got)
	}
}
```

测试组案例 t.Run()

```go
package split

import (
	"reflect"
	"testing"
)

func TestSplit(t *testing.T) {
	//got := Split("我爱爱你", "爱")
	//want := []string{"我", "你"}
	type test struct {
		input string
		sep   string
		want  []string
	}

	tests := map[string]test{
		"简单版本": {
			input: "我爱你",
			sep:   "爱",
			want:  []string{"我", "你"},
		},
		"中间多": {
			input: "a,,,,b,,,,c",
			sep:   ",",
			want:  []string{"a", "b", "c"},
		},
		"前多": {
			input: "爱爱我爱你爱大家",
			sep:   "爱",
			want:  []string{"我", "你", "大家"},
		},
		"后多": {
			input: "a,b,c,,,",
			sep:   ",",
			want:  []string{"a", "b", "c"},
		},
	}

	for testName, testCase := range tests {
		t.Run(testName, func(t *testing.T) {
			got := Split(testCase.input, testCase.sep)
			want := testCase.want
			if !reflect.DeepEqual(got, want) {
				t.Errorf("\nSplit failed!\nwant: %v,\ngot:%v,\n", want, got)
			}
		})
	}
}
```

#### 测试覆盖率

测试覆盖率（Test Coverage）是一种衡量软件测试的度量指标，用于评估测试案例是否覆盖了被测代码的程度。它表示测试中执行到的代码行或代码块在整个代码库中所占的比例。

测试覆盖率常常以百分比的形式呈现，可以衡量以下几个方面：

1. **语句覆盖率（Statement Coverage）**：表示被测试的代码中有多少语句被至少执行一次。它是最基本的覆盖率指标，强调测试是否覆盖了每个语句。

2. **分支覆盖率（Branch Coverage）**：表示被测试的代码中的所有分支（例如 if-else 语句、switch 语句）是否都被执行到。它关注测试是否覆盖了代码中的条件逻辑。

3. **函数覆盖率（Function Coverage）**：表示被测试的代码中有多少函数被至少调用一次。它用于验证是否对每个函数都编写了相应的测试案例。

4. **语句块覆盖率（Basic Block Coverage）**：表示被测试的代码中有多少基本块（Basic Block，通常是编译器生成的中间代码的一部分）被执行到。它比语句覆盖率更细粒度地考虑了代码的执行情况。

高测试覆盖率并不能保证软件没有错误，但它可以帮助发现潜在的问题区域并提供一定的信心。通过提高测试覆盖率，可以增加对代码质量和稳定性的信心，并减少潜在的漏洞和问题。

为了提高测试覆盖率，开发人员需要编写充分的测试案例来覆盖各种情况和边界条件。同时，使用自动化的测试工具和技术（例如单元测试框架、代码覆盖工具）可以帮助更好地跟踪和报告测试覆盖率。

总之，测试覆盖率是一种用于衡量测试案例覆盖程度的指标，旨在提高软件质量和可靠性。它可以帮助开发人员评估测试的有效性，并找到测试中可能存在的盲点和不足之处。

go中测试覆盖率命令

```
go test -cover
```

可视化，将测试覆盖率结果保存成文件

```
go test -cover -coverprofile=<filename>
```

用go tool工具打开该文件，（火狐浏览器访问不了该文件沙比）

```
go tool cover -html=<filename>
```



#### 基准测试

```
go test -bench=<funcName>
```

如，

```
go test -bench=Split
```

额外看内存数据

```
go test -bench=<funcName> -benchmem
```

112 B/op 代表每次操作所使用内存         3 allocs/op 每次操作所申请内存次数

测试代码：

```go
func BenchmarkSplit(b *testing.B) {
	for i := 0; i < b.N; i++ {
		Split("沙河有沙又有河", "有")
	}
}
```

输出结果：

```output
goos: linux
goarch: amd64
pkg: gocommand/split
cpu: 12th Gen Intel(R) Core(TM) i5-12400
BenchmarkSplit-12        9060073               181.0 ns/op           112 B/op          3 allocs/op
PASS
ok      gocommand/split 2.651s
```

修改代码提高性能：

```go
package split

import "strings"

// Split  function will separate the string s by split symbol sep, and return a string slice
// for example, Split("Hello", "e") => ["H", "llo"]
func Split(s, sep string) (ret []string) {
    // here is the modification
	ret = make([]string, 0, strings.Count(s, sep)+1)
	for i := strings.Index(s, sep); i > -1; i = strings.Index(s, sep) {
		aStr := s[:i]
		if aStr != "" {
			ret = append(ret, aStr)
		}
		s = s[i+len(sep):]
	}
	if s != "" {
		ret = append(ret, s)
	}
	return
}
```

输出结果：

```output
goos: linux
goarch: amd64
pkg: gocommand/split
cpu: 12th Gen Intel(R) Core(TM) i5-12400
BenchmarkSplit-12       15933609                86.73 ns/op           48 B/op          1 allocs/op
PASS
ok      gocommand/split 1.461s
```



## 基础语法

### 变量

### 常量

```go
package main

func main() {
	// 不能定义slice常量，slice本身就是可变的，跟常量矛盾了
	const (
		name    = "demon"
		num     = 9 / 3
		isSmart = true
	)
	// 枚举
	const (
		a = iota
		b
		c
		wife   = "Jojo"
		hasSon = true
	)
}
```



### 运算符

#### 自增自减

i++ 和 i--必须独占一行

```go
package main

import "fmt"

func main() {
	i := 20
	i++
	fmt.Printf("i = %v \n", i)
}
```



### 函数

#### 匿名函数

#### 变量作用域

#### 闭包

```go
package main

import (
	"fmt"
	"strings"
)

func addSuffix(suffix string) func(file string) string {
	return func(file string) string {
		if !strings.HasSuffix(file, suffix) {
			return file + suffix
		}
		return file
	}
}

func main() {
	r := addSuffix(".txt")
	fileName := r("python")
	fmt.Printf("file name is %v\n", fileName) // file name is python.txt
}
```



### 流程控制

#### 条件语句

#### 循环语句

### 数据类型

#### 指针

在 Go 语言中，数据类型分为值类型和引用类型（指针类型）。下面是一些常见的数据类型及其分类：

值类型（Value Types）：
- 基本数据类型：如整数类型 (`int`, `int8`, `int16`, `int32`, `int64`), 浮点数类型 (`float32`, `float64`), 布尔类型 (`bool`), 字符串类型 (`string`), 字符类型 (`byte`, `rune`), 复数类型 (`complex64`, `complex128`) 等。
- 数组类型（Array）
- 结构体类型（Struct）

引用类型（Reference Types）：
- 切片类型（Slice）
- 字典类型（Map）
- 通道类型（Channel）
- 函数类型（Function）
- 接口类型（Interface）

需要注意的是，虽然切片、字典、通道、函数和接口等被归类为引用类型，但它们在底层实现上仍然使用了指针。

除了上述类型，还有空值类型（`nil`），它表示一个指向无效对象的指针或引用。例如，`nil` 可以用作指针类型、切片类型、字典类型、通道类型、函数类型和接口类型的零值。

总结一下：
- 值类型在赋值或传递时会进行复制，每个变量都有自己的独立内存空间。
- 引用类型的变量保存的是数据的地址，多个变量指向同一块内存空间。

希望能够解答您的问题！如果还有其他疑问，请随时提出。

#### 自定义类型

##### 类型别名

```go
package main

import "fmt"

// MyInt a custom type based of int type
type MyInt int

// NewInt is a type-alias
type NewInt = int

func main() {
	var i MyInt
	fmt.Printf("type of 'i' is %T ,and its value is %v\n", i, i) // type of 'i' is main.MyInt ,and its value is 0
	var x NewInt
	fmt.Printf("type of 'x' is %T ,and its value is %v\n", x, x) // type of 'x' is int ,and its value is 0
}
```



#### 数组

#####  特性

1. 数组中的元素类型统一
2. 数组定长
3. 数组是值传递，值拷贝

##### 定义

```go
package main

import "fmt"

func main() {
    // 五种定义方式
	var numArr01 [3]int = [3]int{1, 2, 3}
	fmt.Printf("numArr01 =  %v \n", numArr01)

	var numArr02 = [3]int{1, 2, 3}
	fmt.Printf("numArr02 =  %v \n", numArr02)

	var numArr03 = [...]int{1, 2, 3}
	fmt.Printf("numArr03 =  %v \n", numArr03)

	var numArr04 = [...]int{0: 1, 1: 2, 2: 3}
	fmt.Printf("numArr04 =  %v \n", numArr04)

	numArr05 := [...]int{1, 2, 3}
	fmt.Printf("numArr05 =  %v \n", numArr05)
}
```

##### 数组的遍历

```go
package main

import "fmt"

func main() {
	var heroes = [3]string{"demon", "jojo", "hammer"}
	for ind, val := range heroes {
		fmt.Printf("i = %v v = %v \n", ind, val)
		fmt.Printf("heroes[%v]=%v \n", ind, val)
	}

	for _, val := range heroes {
		fmt.Printf("元素的值为%v \n", val)
	}
}
```

#####  修改原数组

```go
package main

import "fmt"

func main() {
	var arr = [3]int{1, 2, 3}
	test(&arr)
	fmt.Printf("arr[0] = %v \n", arr)  //arr[0] = [88 2 3] 
}

// test的参数传入arr的指针，即地址值&arr
func test(arr *[3]int) {
	// 通过指针修改原数组，效率更高，省去了拷贝原数组的过程
	(*arr)[0] = 88
	fmt.Printf("&arr = %p \n", &arr)
}
```



##### 数组练习

习题一

```go 
package main

import "fmt"

func main() {
	// 创建一个byte类型的26个元素的数组放置'A'-'Z'
	// for循环生成并打印
	// 提示： 字符数据运算 'A' + 1  = 'B'
	var alaphs [26]byte
	i := 64
	for index := range alaphs {
		i++
		alaphs[index] = byte(i)
	}

	for _, value := range alaphs {
		fmt.Printf("%c ", value)
	}
}
```

求最大值

```go
package main

import "fmt"

func main() {
	// 算出数组最大值以及下标
	var arr = [5]int{1, -1, 9, 90, 11}
	maxVal, maxIndex := arr[0], 0
	for i, val := range arr {
		if val >= maxVal {
			maxVal, maxIndex = val, i
		}
	}
	fmt.Printf("maxIndex = %d, maxVal = %d \n", maxIndex, maxVal) //maxIndex = 3, maxVal = 90 
}
```

求和（注意强制类型转换来保留小数点）

```go
package main

import "fmt"

func main() {
	// 算出数组的和和平均值
	arr := [5]int{1, -1, 9, 90, 12}
	sum := 0
	for _, val := range arr {
		sum += val
	}
	// 如何让平均值保留小数点
	fmt.Printf("sum = %d , average = %f \n", sum, float64(sum)/float64(len(arr)))
    // sum = 111 , average = 22.200000 
}

```

数组反转打印

```go
package main

import (
	"fmt"
	"math/rand"
)

// 随机生成5个整数并反转打印
func main() {
	// 为了每次生成的随机数不一样，我们给一个seed值
	// rand.Seed(time.Now().UnixNano())
	// 现在自动为全局随机数生成器Int生成一个随机值
	var arr [5]int
	arrLen := len(arr)
	for i := 0; i < arrLen; i++ {
		arr[i] = rand.Intn(100) // 0 <= n < 100
	}
	fmt.Printf("arr = %v \n", arr) //arr = [1 63 37 68 74] 

	for i := 0; i < arrLen/2; i++ {
		arr[arrLen-1-i], arr[i] = arr[i], arr[arrLen-1-i]
	}
	fmt.Printf("arr = %v \n", arr) //arr = [74 68 37 63 1] 
}
```





#### 切片

##### 特性

1. 切片是数组的引用
2. 切片长度可变化
3. 切片从底层来说是一个数据结构（struct结构体）

##### 基本使用

```go
package main

import "fmt"

func main() {
	var arr = [5]int{1, 22, 33, 66, 99}
	var slice = arr[1:3]

	fmt.Printf("arr的地址%p \n", &arr) // arr的地址0xc00001e2d0 

	fmt.Printf("arr[1]的地址%p \n", &arr[1]) // arr[1]的地址0xc00001e2d8 

	fmt.Printf("arr[0]的地址%p \n", &arr[2]) // arr[0]的地址0xc00001e2e0 

	fmt.Printf("slice的地址%p \n", &slice) // slice的地址0xc000010030 

	fmt.Printf("slice[0]的地址%p \n", &slice[0]) // slice[0]的地址0xc00001e2d8 

	fmt.Printf("slice[1]的地址%p \n", &slice[1]) // slice[1]的地址0xc00001e2e0 
}
```



定义切片的另外两种方式

```go
package main

import "fmt"

func main() {
    // 方式2
	var s []float64 = make([]float64, 5, 10)
	s[1], s[3] = 10, 20

	fmt.Printf("s=%v \n", s)
	fmt.Printf("s's len is %v \n", len(s))
	fmt.Printf("s's cap is %v \n", cap(s))
	
    // 方式3
	s1 := []string{"demon", "jojo", "hammer"}
	fmt.Printf("s= %v \n", s1)
	println("长度", len(s1)) // 长度 3
	println("容量", cap(s1)) // 容量 3
}
```



##### 切片遍历

同数组

```go
package main

import "fmt"

func main() {
	var arr = [5]int{10, 20, 30, 40, 50}
	s := arr[1:4]
	for i := 0; i < len(s); i++ {
		fmt.Printf("slice[%v] = %v \n", i, s[i]) // slice[0] = 20 slice[1] = 30 slice[2] = 40
	}

	for i, v := range s {
		fmt.Printf("slice[%v] = %v \n", i, v)
	}
}
```

##### append

##### copy

##### 习题

fibonacci数列

```go
package main

import "fmt"

func main() {
	// 生成一个长度为n的fibonacci数列
	fibonacci := getFibonacci(10)
	fmt.Printf("fibonacci = %v \n", fibonacci)
}

func getFibonacci(n int) []uint64 {
	fibonacci := make([]uint64, n)
	fibonacci[0], fibonacci[1] = 1, 1
	for i := 2; i < n; i++ {
		fibonacci[i] = fibonacci[i-1] + fibonacci[i-2]
	}
	return fibonacci
}
```





#### Map

定义

```go 
package main

import "fmt"

func main() {
	// map定义的三种方式
	// 方式1
	var m1 map[string]string
	m1 = make(map[string]string)
	m1["name"] = "王璞真"
	// 方式2
	var m2 = make(map[string]string)
	m2["nickname"] = "小锤子"
	// 方式3
	var m3 = map[string]string{
		"englishName": "Hammer",
	}
	fmt.Println(m1)
	fmt.Println(m2)
	fmt.Println(m3)
}
```





### 排序

#### 冒泡排序

```go 
package main

import (
	"fmt"
	"time"
)

func main() {
	// 我的版本？？？
	startTime := time.Now().UnixNano()
	var arr = [5]int{24, 69, 80, 57, 13}
	for k := 0; k < len(arr); k++ {
		for i := 0; i < len(arr); i++ {
			for j := i + 1; j < len(arr); j++ {
				if arr[i] > arr[j] {
					if j == len(arr)-1 {
						arr[j], arr[i] = arr[i], arr[j]
					}
					continue
				} else {
					arr[i], arr[j-1] = arr[j-1], arr[i]
					break
				}
			}
		}
	}
	endTime := time.Now().UnixNano()
	deltaTime := endTime - startTime
	fmt.Printf("arr = %v \n", arr)
	fmt.Printf("deltaTime = %v \n", deltaTime)

	// 正确版本
	startTime = time.Now().UnixNano()
	for m := len(arr) - 1; m > 0; m-- {
		for n := 0; n < m; n++ {
			if arr[n] > arr[n+1] {
				arr[n], arr[n+1] = arr[n+1], arr[n]
			}
		}
	}
	endTime = time.Now().UnixNano()
	deltaTime = endTime - startTime

	fmt.Printf("arr = %v \n", arr)
	fmt.Printf("deltaTime = %v \n", deltaTime)

	/* 结果
	arr = [13 24 57 69 80]
	deltaTime = 258
	arr = [13 24 57 69 80]
	deltaTime = 98
	*/
}
```



### 查找

#### 二分查找



### 二维数组

#### 定义

```go
package main

import "fmt"

func main() {
	/*
		0  0  0  0  0  0
		0  0  1  0  0  0
		0  2  0  3  0  0
		0  0  0  0  0  0
	*/
    // 定义二维数组
	var arr [4][6]int
    // 赋值
	arr[1][2] = 1
	arr[2][1] = 2
	arr[2][3] = 3
	for i := 0; i < len(arr); i++ {
		for j := 0; j < len(arr[i]); j++ {
			fmt.Printf("%v  ", arr[i][j])
		}
		println()
	}
}
```

#### 遍历

```go
package main

import "fmt"

func main() {
    /*
    arr[0][0]=1  arr[0][1]=2  arr[0][2]=3  
	arr[1][0]=4  arr[1][1]=5  arr[1][2]=6 
    */
	arr := [2][3]int{{1, 2, 3}, {4, 5, 6}}
	for i, v := range arr {
		for j, v2 := range v {
			fmt.Printf("arr[%v][%v]=%v  ", i, j, v2)
		}
		println()
	}
}
```



### 类型断言

```go 
package main

import "fmt"

type Point struct {
	x, y int
}

func main() {
	var a interface{}
	point := Point{1, 2}
	// 将point值赋给一个空接口，空接口类型可以接受任何值，但是不会改变空接口的类型，
	//因此a变量还是空接口类型，不能确定a变量，但是类型断言就是告诉编译器，a存的值是一个Point类型
	a = point
	// b = a 不行
	// var b Point
	// b = a.(Point)可以
	// 直接用自动推导也可以，但是如果变量的赋值是动态的或依赖于运行时的计算则无法用自动推导
	b := a
	fmt.Printf("b的类型是%T, b=%+v \n", b, b)
}
```



带检测的类型断言

```go 
package main

import "fmt"

func main() {
	var x interface{}
	var b float32 = 1.1
	x = b
	y, ok := x.(float32)
	if ok {
		println("convert successes")
		fmt.Printf("Type of y is %T, and value is %v \n", y, y)
	} else {
		println("convert fails")
	}
	println("go ahead")
}
```



最佳实践

```go 
package main

import "fmt"

type Usb interface {
	Start()
	Stop()
}

type Phone struct {
	name string
}

func (p Phone) Start() {
	//TODO implement me
	fmt.Printf("手机%v开始工作 \n", p.name)
}

func (p Phone) Stop() {
	//TODO implement me
	fmt.Printf("手机%v停止工作 \n", p.name)
}

func (p Phone) call() {
	fmt.Printf("手机%v打电话。。。 \n", p.name)
}

type Camera struct {
	name string
}

func (c Camera) Start() {
	//TODO implement me
	fmt.Printf("相机%v开始工作 \n", c.name)
}

func (c Camera) Stop() {
	//TODO implement me
	fmt.Printf("相机%v停止工作 \n", c.name)
}

type Computer struct {
}

func (c Computer) Working(usb Usb) {
	usb.Start()
	usb.Stop()
	// 如果usb是手机结构体变量，则还需调用call方法
	if phone, ok := usb.(Phone); ok {
		phone.call()
	}
}

func main() {
	var usbArr [3]Usb
	usbArr[0] = Phone{"iphone"}
	usbArr[1] = Phone{"huawei"}
	usbArr[2] = Camera{"sony"}
	var computer Computer
	for _, usb := range usbArr {
		computer.Working(usb)
	}
}
```



## 标准库

### fmt

fmt.print, fmt.println, fmt.printf

#### printf的通用占位符

| 占位符 | 说明                                 |
| ------ | ------------------------------------ |
| %v     | 值的默认格式表示                     |
| %+v    | 输出结构体时会自动添加字段名         |
| %#v    | 会展示GO中如何表示该值               |
| %T     | 打印值的类型                         |
| %%     | 想打印百分号那只能输入这两个百分号了 |

案例：

```go
type User struct {
	Id int64
}

func TestPrintf1(t *testing.T) {
	user := &User{Id: 1}
	fmt.Printf("%v\n", user)
	fmt.Printf("%+v\n", user)
	fmt.Printf("%#v\n", user)
	fmt.Printf("%T\n", user)
	fmt.Printf("%%\n")
}
```

输出结果：

&{1}
&{Id:1}
&fmttest.User{Id:1}
*fmttest.User
%

#### 布尔型占位符

| 占位符 | 说明       |
| ------ | ---------- |
| %t     | 打印bool值 |

案例：

```go
func TestPrintf2(t *testing.T) {
	fmt.Printf("%t\n", true)
}
```

结果：

```
=== RUN   TestPrintf2
true
--- PASS: TestPrintf2 (0.00s)
PASS
```

> 如果用%v打印bool值会有什么效果？
>
> 答：会正常打印出true，有点意思哈～

#### 整型占位符

| 占位符 | 说明                                                      |
| ------ | --------------------------------------------------------- |
| %b     | 二进制                                                    |
| %c     | 打印unicode字符                                           |
| %d     | 十进制                                                    |
| %o     | 八进制                                                    |
| %x     | 十六进制，用a-f表示                                       |
| %X     | 十六进制，用A-F表示                                       |
| %U     | 打印Unicode码点                                           |
| %q     | go语法字符字面值，也是unicode字符（打印结果会多个''包裹） |

```go
func TestPrintf3(t *testing.T) {
	n := 180
	fmt.Printf("%b\n", n)
	fmt.Printf("%c\n", n)
	fmt.Printf("%d\n", n)
	fmt.Printf("%o\n", n)
	fmt.Printf("%x\n", n)
	fmt.Printf("%X\n", n)
	fmt.Printf("%U\n", n)
	a := 96
	fmt.Printf("%q\n", a)
	fmt.Printf("%q\n", 0x4E2D)
}
```

输出结果

```
10110100
´
180
264
b4
B4
U+00B4
'`'
'中'
```

#### 浮点数占位符

| 占位符 | 说明                                 |
| ------ | ------------------------------------ |
| %b     | ？？？回头再整理                     |
| %e     | 科学计数法，如-1234.4566e+78         |
| %E     | 科学计数法，如-1234.4566E+78         |
| %f     | 123.456                              |
| %F     | 等于%f                               |
| %g     | 根据实际情况决定是用%e格式还是%f格式 |
| %G     | 大写的g                              |

案例

```go
func TestPrintf4(t *testing.T) {
	n := 18.54
	fmt.Printf("%b\n", n)
	fmt.Printf("%e\n", n)
	fmt.Printf("%E\n", n)
	fmt.Printf("%f\n", n)
    fmt.Printf("%.2f\n", n)
	fmt.Printf("%F\n", n)
	fmt.Printf("%g\n", n)
	fmt.Printf("%G\n", n)
}
```

输出结果

```
5218546068215562p-48
1.854000e+01
1.854000E+01
18.540000
18.54
18.540000
18.54
18.54
```

#### 字符串占位符

| 占位符 | 说明             |
| ------ | ---------------- |
| %s     | 字符串或者[]byte |
| %q     | 同上面           |
| %x     | 同上             |
| %X     | 同上             |

案例

```go
func TestPrintf5(t *testing.T) {
	s := "我是字符串"
	b := []byte{65, 66, 67}
	fmt.Printf("%s\n", s)
	fmt.Printf("%s\n", b)
	fmt.Printf("%q\n", s)
	fmt.Printf("%x\n", s)
	fmt.Printf("%X\n", s)
}
```

输出结果

```
我是字符串
ABC
"我是字符串"
e68891e698afe5ad97e7aca6e4b8b2
E68891E698AFE5AD97E7ACA6E4B8B2
```

#### 指针占位符

| 占位符 | 说明 |
| ------ | ---- |
| %p     |      |

```go
func TestPrintf6(t *testing.T) {
	ptr := &User{Id: 1}
	fmt.Printf("%p\n", ptr)
}
```

结果

```
0xc000028350
```

#### 宽度占位符



#### 其他占位符





### os

常用函数

| 函数名    | 作用                   | 参数 类型     | 返回值 类型                     | 其他备注               |
| --------- | ---------------------- | ------------- | ------------------------------- | ---------------------- |
| Create    | 创建文件，已存在则清空 | 文件名 string | 1. 该文件指针 *file<br />2. err | err类型是*os.pathError |
| Mkdir     | 创建单个目录           |               |                                 |                        |
| MkdirAll  |                        |               |                                 |                        |
| Remove    |                        |               |                                 |                        |
| RemoveAll |                        |               |                                 |                        |
|           |                        |               |                                 |                        |





## 面对对象

oop

## 并发编程

### 协程

#### 入门案例

使用go关键字开启一个协程

```go
package main

import "time"

// 在主线程中开启一个协程，每隔1秒输出hello world
// 在主线程中每隔1秒输出一个hello golang
func test() {
	for i := 0; i < 10; i++ {
		println("hello, world")
		time.Sleep(time.Second)
	}
}

func main() {
	go test()

	for i := 0; i < 5; i++ {
		println("hello, golang")
		time.Sleep(time.Second)
	}
}
```

调度模型

MPG模式

- M：操作系统主线程（物理线程）
- P：上下文
- G：协程



#### 提前退出协程

```go
package main

import (
	"runtime"
	"time"
)

func main() {
	go func() {
		func() {
			println("这是goroutine内部的函数！")
			//return // 退出当前函数
			//os.Exit(22) // 退出进程
			runtime.Goexit() // 退出goroutine
		}()
		println("goroutine结束")
	}()
	println("这是主进程")
	time.Sleep(time.Second * 5)
	println("over")
}
```





### 管道channel

#### 特性

- 本质是队列（FIFO）
- 线程安全，多个协程操作同一个管道时，不会有资源竞争

#### 定义

```go
package main

import "fmt"

func main() {
	var intChan chan int
	intChan = make(chan int, 3)
	fmt.Printf("引用类型存的值%v \n引用类型自己的地址%p \n", intChan, &intChan)
	// 写入值
	intChan <- 10
	num := 211
	intChan <- num
	intChan <- 50
	// 查看管道的长度和cap
	fmt.Println("管道的长度", len(intChan))
	fmt.Println("管道的容量", cap(intChan))

	// 取值
	num2 := <-intChan
	fmt.Println("num2 = ", num2)
}
```

#### 案例（类型断言）

```go
package main

import "fmt"

type Cat struct {
	Name string
	Age  int
}

func main() {
	allChan := make(chan interface{}, 3)
	//allChan <- 10
	//allChan <- "hammer"
	cat := Cat{
		Name: "demon",
		Age:  18,
	}
	allChan <- cat
	newCat := <-allChan
	fmt.Printf("type of newCat is %T\nnewCat's value is %v\n", newCat, newCat)
	a := newCat.(Cat)
	fmt.Printf("newCat.name is %v\n", a.Name)
}
```



#### 关闭管道 close

管道关闭之后，只能从管道读数据，不能向管道写数据。

当读写管道的次数不对等时，比如，可以在一个for循环中一直读数据，而关闭管道的目的是让读取管道者（某个goroutine）知道，在读完管道内已有的数据后，不会再有新数据往管道中写入了，那读取管道者就可以在此处停止读取，而不是继续等待管道输出数据，这样可以有效避免读取管道者发生死锁的情况，例如下面这段代码，当管道关闭且数据被读完时，读取管道者就拿到值为false的ok变量以及关闭的管道发送的零值（管道关闭后，读取者会在所有数据的最后读到一个零值而终止继续等待读取数据），进而跳出循环：

```go
num, ok = <-numCh
		if !ok {
			// 取不到数了就跳出循环
			break
		}
```



```go
package main

func main() {
	intChan := make(chan int, 3)
	intChan <- 100
	intChan <- 200
	close(intChan)
	// 关闭管道后可以读取数据
	num := <-intChan // 100
	println(num)
	// 关闭管道后不能写入数据
	intChan <- 300
	println("关闭管道了")
}
```

在Go语言中，要打印管道（channel）中存放的值，需要使用`range`关键字来遍历管道。以下是一个示例代码：

```go
package main

import "fmt"

func main() {
    // 创建一个整型管道
    ch := make(chan int)

    // 启动一个并发的goroutine，向管道发送数据
    go func() {
        for i := 1; i <= 5; i++ {
            ch <- i // 发送数据到管道
        }
        close(ch) // 关闭管道
    }()

    // 遍历管道中的值并进行打印
    for value := range ch {
        fmt.Println(value)
    }
}
```

> 为什么要先关闭才能打印？

在Go语言中，关闭管道是一个重要的操作步骤，并且对于遍历管道来说，关闭管道具有特殊的作用。下面我将解释为什么要先关闭管道才能打印。

首先，关闭管道是用来告知接收方（遍历管道的循环）不会再有更多的数据发送到管道中了。这样可以使接收方得知数据已经全部发送完毕，从而跳出循环，避免无限等待新的数据到达的情况。如果没有关闭管道，遍历的循环将会一直阻塞，除非有明确的退出条件。

其次，对于`range`关键字用于遍历管道，它会在管道关闭后自动跳出循环。这意味着，只有当管道关闭后，`range`循环才能结束。在遍历过程中，如果没有关闭管道，那么`range`循环将会一直等待接收到新的数据，造成程序无法继续往下执行。

因此，为了避免遍历管道时的阻塞，以及确保`range`循环能够正常结束，我们需要在数据发送完毕后显式地关闭管道。

需要注意的是，关闭管道是发送方的责任。关闭已经关闭的管道或者向已经关闭的管道发送数据都会导致运行时错误。因此，在关闭管道之前，发送方应该确保所有数据都已经发送完毕。

综上所述，关闭管道是为了通知接收方数据发送已经完成，并且在使用`range`遍历管道时，关闭管道能够使循环正常结束。





#### 阻塞机制

1. 有缓冲可以先写后读，但不能超过管道容量
2. 无缓冲必须写一个才能读一个

```go
package main

import (
	"time"
)

func main() {
	// 创建装数字的管道
	numC := make(chan int, 10)
	go func() {
		for i := 0; i < 50; i++ {
			data := <-numC
			println("读 ===>", data)
			time.Sleep(time.Second * 1)
		}
	}()

	for i := 0; i < 50; i++ {
		numC <- i
		println("写 --->", i)
		//time.Sleep(time.Second * 1)
	}
	time.Sleep(time.Second * 1)
	close(numC)
	for value := range numC {
		println(value)
	}
}
```

#### select语法

select不需要关闭管道？？？？

如果是主线程运行管道就不用，但是协程运行管道不关闭的话，怎么知道什么时候停止写入数据了？

```go
package main

import (
	"fmt"
	"strconv"
	"time"
)

func main() {
	numCh := make(chan int, 10)
	strCh := make(chan string, 5)
	go func() {

		for i := 0; i < 10; i++ {
			numCh <- i
		}

		for i := 0; i < 5; i++ {
			strCh <- "hello" + strconv.Itoa(i)
		}
	}()

label:
	for {
		select {
		case v := <-numCh:
			fmt.Printf("从numCh中读取数据%d\n", v)
		case v := <-strCh:
			fmt.Printf("从strCh中读取数据%s\n", v)
		default:
			println("数据取完")
			time.Sleep(time.Second)
			// return
			break label
		}
	}
}
```



#### 单向管道

定义

```go
package main

import "fmt"

func main() {
	// 普通管道
	ch := make(chan int, 10)
	ch <- 2
	close(ch)
	for v := range ch {
		fmt.Printf("v=%v\n", v) // v=2
	}
	// 只写管道
	ch1 := make(chan<- string, 3)
	ch1 <- "hammer"
	fmt.Printf("ch1=%v\n", ch1) // ch1=0xc00002e1e0
	// 只读管道
	ch2 := make(<-chan bool, 1)
	//b := <-ch2
	fmt.Printf("ch2=%v\n", ch2) // ch2=0xc00002a0e0
}
```





#### 应用案例

代码有问题

```go 
package main

// write data
func writeData(intChan chan int) {
	for i := 0; i < 50; i++ {
		intChan <- i + 1
		println("写入数据：", i)
	}
	close(intChan)
}

// read data
func redaData(intChan chan int, exitChan chan bool) {
	for {
		v, ok := <-intChan
		if !ok {
			break
		}
		println("读出数据：", v)
	}
	exitChan <- true
	close(exitChan)
}

func main() {
	//创建两个管道
	intChan := make(chan int, 50)
	exitChan := make(chan bool, 1)
	go writeData(intChan)
	go redaData(intChan, exitChan)
	for {
        // 这里ok或者!ok都可以，为什么？
		if v, ok := <-exitChan; !ok {
			println(v)
			println(ok)
			break
		}
	}
    
    // 直接在这等exitchan取值也行
    // v := <-exitChan
	// println(v)
}
```



统计1-80000中的素数

```go
package main

func calPrimeNum(numCh chan int, primeCh chan int, exitCh chan bool) {
	var num int
	var numIsPrime bool
	var ok bool
	for {
		// 一直从管道里取数
		num, ok = <-numCh
		if !ok {
			// 取不到数了就跳出循环
			break
		}
		numIsPrime = true
		// 判断该数是不是素数
		// 先假定为素数,
		for i := 2; i < num; i++ {
			// 除以i,余数为0,则不是素数
			if num%i == 0 {
				// 判定该数非素数，跳出循环后，不会当作素数存进管道
				numIsPrime = false
				break
			}
		}
		if numIsPrime {
			primeCh <- num
		}
	}
	println("该goroutine完成工作退出 ")

	// 向exitCh写入标记
	exitCh <- true
}

func main() {
	numCh := make(chan int, 1000)
	primeNumCh := make(chan int, 1000)
	exitCh := make(chan bool, 4)
	//开启goroutine放入数据
	go func() {
		for i := 2; i <= 8000; i++ {
			numCh <- i
		}
		// 这里为什么必须关闭？
		close(numCh)
	}()

	// 开启4个goroutine
	for i := 0; i < 4; i++ {
		go calPrimeNum(numCh, primeNumCh, exitCh)
	}

	go func() {
		for i := 0; i < 4; i++ {
			<-exitCh
		}

		close(primeNumCh)
	}()

	for {
		primeNum, ok := <-primeNumCh
		if !ok {
			break
		}
		println("1-8000中的素数：", primeNum)
	}
}
```



与单线程速度对比，12核cpu

这是12个goroutine跑出来的结果，耗时2442.35微妙

```go
package main

import (
	"fmt"
	"time"
)

func calPrimeNum(numCh chan int, primeCh chan int, exitCh chan bool) {
	var num int
	var numIsPrime bool
	var ok bool
	for {
		// 一直从管道里取数
		num, ok = <-numCh
		if !ok {
			// 取不到数了就跳出循环
			break
		}
		// 判断该数是不是素数
		// 先假定为素数
		numIsPrime = true

		for i := 2; i < num; i++ {
			// 除以i,余数为0,则不是素数
			if num%i == 0 {
				// 判定该数非素数，跳出循环后，不会当作素数存进管道
				numIsPrime = false
				break
			}
		}
		if numIsPrime {
			primeCh <- num
		}
	}
	//println("该goroutine完成工作退出 ")

	// 向exitCh写入标记
	exitCh <- true
}

func main() {
	// 统计时间
	start := time.Now().UnixMicro()
	// 执行100次
	for i := 0; i < 100; i++ {
		numCh := make(chan int, 8000)
		primeNumCh := make(chan int, 3000)
		exitCh := make(chan bool, 12)

		//开启goroutine放入数据
		go func() {
			for i := 2; i <= 8000; i++ {
				numCh <- i
			}
			// 这里为什么必须关闭？
			close(numCh)
		}()

		// 开启12个goroutine
		for i := 0; i < 12; i++ {
			go calPrimeNum(numCh, primeNumCh, exitCh)
		}

		go func() {
			for i := 0; i < 12; i++ {
				<-exitCh
			}

			close(primeNumCh)
		}()

		for {
			_, ok := <-primeNumCh
			if !ok {
				break
			}
			//println("1-8000中的素数：", primeNum)
		}
	}

	end := time.Now().UnixMicro()
	averTime := float64(end-start) / 100.0

	fmt.Printf("averTime=%.2f", averTime) // averTime=2442.35
}
```



单线程耗时：*8767.15*微秒

```go
package main

import (
	"fmt"
	"time"
)

func getPrimeNum(primeCh chan int) {
	var numIsPrime bool
	for num := 2; num < 8000; num++ {
		// 判断该数是不是素数
		// 先假定为素数
		numIsPrime = true

		for i := 2; i < num; i++ {
			// 除以i,余数为0,则不是素数
			if num%i == 0 {
				// 判定该数非素数，跳出循环后，不会当作素数存进管道
				numIsPrime = false
				break
			}
		}
		if numIsPrime {
			primeCh <- num
		}
	}
}

func main() {
	start := time.Now().UnixMicro()
	// 执行100次
	for i := 0; i < 100; i++ {
		primeCh := make(chan int, 3000)
		getPrimeNum(primeCh)
	}
	end := time.Now().UnixMicro()
	averTime := float64(end-start) / 100.0

	fmt.Printf("averTime=%.2f", averTime) // averTime=8767.15
}
```



## 反射

### 概念

反射（reflection）是一种机制，用于在运行时检查和操作程序的结构，包括类型和变量等信息。它提供了一种动态的方式来获取和操作对象的属性、方法和类型等信息。

反射在 Go 中广泛应用于一些场景，例如：

1. 动态地获取和设置变量的值。
2. 动态地创建和调用函数。
3. 解析和处理结构体的字段和标签。
4. 通过接口来处理任意类型的对象等。

### 入门案例

```go
package main

import (
	"fmt"
	"reflect"
)

func refTest01(v interface{}) {
	// 通过反射获取到传入变量的type， kind， value
	// 就把这里的refType和refValue理解成对象
	refType := reflect.TypeOf(v)
	fmt.Printf("TypeOf返回的值%v\n", refType)  // int
	fmt.Printf("TypeOf返回的类型%T\n", refType) //*reflect.rtype

	refValue := reflect.ValueOf(v)
	fmt.Printf("ValueOf返回的值%v\n", refValue)  // 100
	fmt.Printf("ValueOf返回的类型%T\n", refValue) // reflect.Value

	num := 26 + refValue.Int()
	println("num=", num) // 126

	// 转回接口
	interValue := refValue.Interface()
	fmt.Printf("Interface返回的值%v\n", interValue)  // 100
	fmt.Printf("Interface返回的类型%T\n", interValue) // int

	// 通过类型断言将空接口转成int
	num2 := interValue.(int)
	println(num2) // 100

}

func main() {
	num := 100
	refTest01(num)
}
```

#### 关于类型断言的必要性

```go
package main

import (
	"fmt"
	"reflect"
)

func refTest(v interface{}) {
	value := reflect.ValueOf(v)
	interValue := value.Interface()
	fmt.Printf("interface返回的值：%v\n", interValue)  // {Demon 27}
	fmt.Printf("Interface返回的类型：%T\n", interValue) //main.Student
	// 如果这里不使用类型断言，则编译器无法编译print里的stu.Name, stu.Age
	// 另外可以用switch case来处理不同的结构体类型
	stu, ok := interValue.(Student)
	if ok {
		fmt.Printf("stu.Name=%v\nstu.Age=%v\n", stu.Name, stu.Age) //stu.Name=Demon stu.Age=27
	}
}

type Student struct {
	Name string
	Age  int
}

func main() {
	stu := Student{
		Name: "Demon",
		Age:  27,
	}
	refTest(stu)
}
```

#### kind()

```go
package main

import (
	"fmt"
	"reflect"
)

func refTest(v interface{}) {
	value := reflect.ValueOf(v)
	valType := reflect.TypeOf(v)
	valueKind := value.Kind()
	// 这个kind方法等价于上面的kind方法
	valTypeKind := valType.Kind()
	println(valueKind == valTypeKind)           // true
	fmt.Printf("valueKind=%v\n", valueKind)     // valueKind=struct
	fmt.Printf("valTypeKind=%v\n", valTypeKind) // valTypeKind=struct
	//interValue := value.Interface()
}

type Student struct {
	Name string
	Age  int
}

func main() {
	stu := Student{
		Name: "Demon",
		Age:  27,
	}
	refTest(stu)
}
```

#### Elem()

```go
package main

import (
	"fmt"
	"reflect"
)

func reflect01(v interface{}) {
	refVal := reflect.ValueOf(v)
	fmt.Printf("kind=%v\n", refVal.Kind()) // ptr
	refVal.Elem().SetInt(50)
}

func main() {
	// 通过反射修改值
	var num = 1
	reflect01(&num)
	fmt.Printf("num=%v\n", num) // 50
}
```



## 网络编程

### 入门案例

服务器端

```go
// server.go
package main

import (
	"fmt"
	"net"
)

func process(conn net.Conn) {
	defer func() {
		_ = conn.Close()
	}()
	for {
		//创建一个新的切片
		buf := make([]byte, 1024)
		// 重要：客户端不发送，则协程一直阻塞在此
		//fmt.Printf("服务器等待客户端%v发送消息\n", conn.RemoteAddr().String())
		n, err := conn.Read(buf)
		// 或者if err == os.EOF {}
		if err != nil {
			fmt.Printf("server read error:%v\n", err)
			return
		}
		// 打印数据
		fmt.Printf("服务器接受数据成功：%v\n", string(buf[:n]))
	}
}

func main() {
	println("服务器开始监听")
	listener, err := net.Listen("tcp", "0.0.0.0:45678")
	if err != nil {
		println("监听出错：", err)
	}
	// 及时退出
	defer func() {
		_ = listener.Close()
	}()
	//看看listener到底是啥
	fmt.Printf("listener is %v\n", listener) // &{0xc000112000 {<nil> 0}}
	// 循环等到不同客户端连接
	for {
		// Accept()使服务器阻塞等待客户端连接
		conn, err := listener.Accept()
		if err != nil {
			println("连接出错：", err)
		} else {
			println("客户端Ip为", conn.RemoteAddr().String())
		}
		// 看看conn是啥
		fmt.Printf("conn is %v\n", conn)
		// 分发到某个协程去处理该客户端的任务
		go process(conn)
	}
}
```

客户端

```go
// client.go
package main

import (
	"bufio"
	"net"
	"os"
	"strings"
)

func main() {
	conn, err := net.Dial("tcp", "0.0.0.0:45678")
	if err != nil {
		println("Dial error:", err)
		return
	}
	println("客户端连接成功，conn=", conn)

	reader := bufio.NewReader(os.Stdin)
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			println("readString error :", err)
		}
		// 如果用户输入exit就退出
		line = strings.Trim(line, " \r\n")
		if line == "exit" {
			println("客户端退出")
			break
		}
		_, err = conn.Write([]byte(line))
		if err != nil {
			println("write error:", err)
		}
		//fmt.Printf("客户端发送了%d字节的数据\n", n)
	}
}
```



## Redis

snap安装redis

```bash
snap install redis
```

启动redis

```
redis.cli
```

redis指令参考网站：http://redisdoc.com/

查看指令

```
redis.cli --help
```



## go todolist 项目

是的，我可以为你提供一个用Go语言开发命令行待办事项清单（Todo List）项目的简单示例。以下是一个基本的实现步骤：

1. 初始化项目：创建一个新的文件夹来存放项目代码，并初始化一个新的Go模块。在终端中执行以下命令：

   ```shell
   mkdir todolist
   cd todolist
   go mod init github.com/yourusername/todolist
   ```

2. 添加所需的依赖库：在项目文件夹中创建一个 `main.go` 文件，并添加以下代码来导入所需的依赖库。

   ```go
   package main

   import (
   	"fmt"
   	"os"
   	"bufio"
   )
   ```

3. 定义任务结构：在 `main.go` 文件中定义一个代表任务的结构体类型，并添加一些必要的字段。

   ```go
   type Task struct {
   	ID   int
   	Name string
   }
   ```

4. 实现待办事项的功能：添加以下代码来实现待办事项的增删查操作。

   ```go
   func addTask(tasks []Task, name string) []Task {
   	taskID := len(tasks) + 1
   	newTask := Task{
   		ID:   taskID,
   		Name: name,
   	}
   	tasks = append(tasks, newTask)
   	return tasks
   }

   func deleteTask(tasks []Task, id int) []Task {
   	for i, task := range tasks {
   		if task.ID == id {
   			tasks = append(tasks[:i], tasks[i+1:]...)
   			break
   		}
   	}
   	return tasks
   }

   func listTasks(tasks []Task) {
   	if len(tasks) == 0 {
   		fmt.Println("No tasks found.")
   		return
   	}
   	for _, task := range tasks {
   		fmt.Printf("[%d] %s\n", task.ID, task.Name)
   	}
   }
   ```

5. 实现用户交互逻辑：添加以下代码来实现用户输入和命令解析的逻辑。

   ```go
   func getUserInput(prompt string) string {
   	reader := bufio.NewReader(os.Stdin)
   	fmt.Print(prompt)
   	input, _ := reader.ReadString('\n')
   	return strings.TrimSpace(input)
   }

   func parseCommand(command string) (string, int) {
   	fields := strings.Fields(command)
   	if len(fields) == 0 {
   		return "", 0
   	}
   	switch fields[0] {
   	case "add":
   		if len(fields) < 2 {
   			return "", 0
   		}
   		return "add", fields[1]
   	case "delete":
   		if len(fields) < 2 {
   			return "", 0
   		}
   		taskID, err := strconv.Atoi(fields[1])
   		if err != nil {
   			return "", 0
   		}
   		return "delete", taskID
   	case "list":
   		return "list", 0
   	default:
   		return "", 0
   	}
   }
   ```

6. 主函数逻辑：在 `main` 函数中添加以下代码来组织主要的工作流程。

   ```go
   func main() {
   	var tasks []Task

   	for {
   		command := getUserInput("Enter a command (add/delete/list): ")
   		action, value := parseCommand(command)

   		switch action {
   		case "add":
   			tasks = addTask(tasks, value)
   			fmt.Println("Task added.")
   		case "delete":
   			tasks = deleteTask(tasks, value)
   			fmt.Println("Task deleted.")
   		case "list":
   			listTasks(tasks)
   		default:
   			fmt.Println("Invalid command. Try again.")
   		}
   	}
   }
   ```

7. 编译和运行：在项目文件夹中打开终端，执行以下命令来编译和运行项目。

   ```shell
   go build
   ./todolist
   ```

这只是一个简单的示例，用于说明如何使用Go语言开发命令行待办事项清单项目。你可以根据项目需求和个人偏好进行相应地定制和扩展。同时，你也可以考虑使用第三方库来增强功能，如处理命令行参数的 `flag` 包、存储数据的数据库驱动等。

希望这个示例对你有所帮助！