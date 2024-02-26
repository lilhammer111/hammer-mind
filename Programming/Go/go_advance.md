# Error

## Error type

### Sentinel error

尽可能避免使用sentinel error

### Error types

### Opaque errors

## Handling Error

案例一：

```go
func AuthenticateRequest(r *Request) error {
	err := authenticate(r.User)
	if err != nil {
		return err
	}
	return nil
}
```

因为返回值是err，所以可以直接返回。改进后：

```go
func AuthenticateRequest(r *Request) error {
    return authenticate(r.User)
}
```



案例二，统计io.Reader读取内容的行数

```go
func CountLines(r io.Reader) (int, error) {
    var (
        br = bufio.NewReader(r)
        lines int
        err error
    )
    
    for {
        _, err = br.ReadString('\n')
        lines++
        if err != nil {
            break
        }
    }
    
    if err != io.EOF {
		return 0, err
    }
    return lines, nil
}
```

利用Scanner结构体中的Err()方法获取暂存的error

```go
func CountLines(r io.Reader) (int, error) {
	sc := bufio.NewScanner(r)
	lineNum := 0
	for sc.Scan() {
		lineNum++
	}

	return lineNum, sc.Err()
}
```

### wrap errors

#### 借助第三方库：github.com/pkg/errors

##### wrap()

##### wraps()



#### 1.13版本后的go

使用`fmt.Errorf()`和`%w`来包装底层错误:

```go
package main

import (
	"fmt"
	"io/ioutil"
)

func main() {
	filename := "example.txt"
	content, err := readFile(filename)
	if err != nil {
		fmt.Println(err)
		return
	}
	
	fmt.Println("File content:", string(content))
}

func readFile(filename string) ([]byte, error) {
	content, err := ioutil.ReadFile(filename)
	if err != nil {
		// 使用 fmt.Errorf 包装底层错误
		return nil, fmt.Errorf("failed to read file: %w", err)
	}
	
	return content, nil
}
```

输出结果：

```
failed to read file: open example.txt: no such file or directory
```





使用`errors.Is()`和`errors.As()`函数

```go
package main

import (
	"errors"
	"fmt"
	"os"
)

type CustomError struct {
	Code    int
	Message string
}

func main() {
	err := process()

	// 使用 errors.Is() 检查特定类型的错误
	if errors.Is(err, os.ErrNotExist) {
		fmt.Println("文件不存在")
	} else if errors.Is(err, os.ErrPermission) {
		fmt.Println("无权限访问文件")
	} else if customErr, ok := errors.As(err, &CustomError{}); ok {
		fmt.Printf("自定义错误：Code=%d, Message=%s\n", customErr.Code, customErr.Message)
	} else {
		fmt.Println("发生未知错误")
	}
}

func process() error {
	file := "example.txt"
	_, err := os.Open(file)
	if err != nil {
		// 返回特定类型的自定义错误
		return &CustomError{
			Code:    100,
			Message: "打开文件失败",
		}
	}

	return nil
}
```

