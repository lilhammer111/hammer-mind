# grpc

## 使用protobuf

### 官网

https://protobuf.dev/getting-started/gotutorial/

### 文件目录及格式

创建目录proto

创建protobuf文件，文件名xx.proto

### 定义protobuf文件

```protobuf
syntax = "proto3";

service Hello {
  rpc Hello(HelloRequest) returns (Response); // Hello interface
}

message HelloRequest {
  string name = 1; // 1 is not value but an ID
  int32 age = 2;
  repeated string course = 3;
}

message Response {
  string reply = 1;
}
```

### 安装依赖

原先是使用

```shell
 go get -u github.com/golang/protobuf/protoc-gen-go
```

但是现在已经废弃，结果：

go: module github.com/golang/protobuf is deprecated: Use the "google.golang.org/protobuf" module instead.



ubuntu系统下可以直接通过snap安装protobuf:

```shell
snap install --classic protobuf
```





### 生成xx.pb.go源码

```shell
protoc --go_out=. --go-grpc_out=. *.proto 
```



## grpc初体验（simple RPC）

### 项目目录结构

```shell
.
├── client
│   └── client.go
├── go.mod
├── go.sum
├── proto
│   ├── helloworld_grpc.pb.go
│   ├── helloworld.pb.go
│   └── helloworld.proto
└── server
    └── server.go
```

### server.go代码

```go
package main

import (
	"context"
	"google.golang.org/grpc"
	"gprc_test/proto"
	"log"
	"net"
)

type Server struct {
	*proto.UnimplementedGreeterServer
}

func (s *Server) SayHello(ctx context.Context, request *proto.HelloRequest) (*proto.HelloReply, error) {
	return &proto.HelloReply{Message: "Hello" + request.Name}, nil
}

func main() {
	g := grpc.NewServer()
	proto.RegisterGreeterServer(g, &Server{})
	lis, err := net.Listen("tcp", "127.0.0.1:8080")
	if err != nil {
		log.Fatal("127.0.0.1:8080 listening failed")
	}
	err = g.Serve(lis)
	if err != nil {
		log.Fatal("g serve failed")
	}
}
```

关键点，通过Server结构体嵌套`*proto.UnimplementedGreeterServer`结构体，完成空实现，否则`proto.RegisterGreeterServer(g, &Server{})`传入` &Server{}`时报错。

报错内容：

> ./server.go:19:33: cannot use &Server{} (value of type *Server) as "gprc_test/proto".GreeterServer value in argument to proto.RegisterGreeterServer: *Server does not implement "gprc_test/proto".GreeterServer (missing method mustEmbedUnimplementedGreeterServer)



### client.go代码

```go
package main

import (
	"context"
	"google.golang.org/grpc"
	"gprc_test/proto"
	"log"
)

func main() {
	conn, err := grpc.Dial(":8080", grpc.WithInsecure())
	if err != nil {
		log.Fatal("dial failed ", err)
	}
	defer func() {
		err = conn.Close()
		if err != nil {
			return
		}
	}()

	c := proto.NewGreeterClient(conn)
	r, err := c.SayHello(context.Background(), &proto.HelloRequest{Name: "Demon"})
	if err != nil {
		log.Fatal("make sure your target is written correctly, because ", err)
	}
	log.Println(r.Message)
}
```



### RPC模式

1. 简单流模式 Simple RPC

2. 服务端数据流模式 Server-side streaming RPC

典例：股票就是这种模式

3. 客户端数据流模式 Client-side streaming RPC

典例：物联网终端向服务器报送数据

4. 双向数据流模式 Bidirectional streaming RPC

典例：聊天机器人



## option go_package 的作用

```protobuf
option go_package = "common/stream/proto/v1";
```

可以在当前目录下使用protoc编译命令生成这样一些文件夹路径，v1是包名





