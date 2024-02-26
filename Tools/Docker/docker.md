拉取镜像

```shell
docker pull mysql
```

生成实例

```shell
docker run -p 3339:3306 --name mysql-master -e MYSQL_ROOT_PASSWORD=root -d mysql
```

查看正在运行的docker实例，如果所有 -a

```shell
docker ps -a
```

删除docker实例

```shell
docker rm mysql-slave
```

进入bash

```shell
docker exec -it mysql-master bash
```

重启docker实例

```shell
docker restart mysql-master
```



Docker 是一个开源的应用容器引擎，允许开发者打包应用及其依赖包到一个可移植的容器中，然后发布到任意的 Linux 机器上。以下是一些 Docker 的常用命令：

1. **镜像相关命令**：
   - `docker images`: 列出本地的所有镜像。
   - `docker rmi [IMAGE]`: 删除一个或多个镜像。
   - `docker pull [IMAGE]`: 下载一个镜像。
   - `docker build -t [IMAGE_NAME]:[TAG] .`: 使用当前目录的 Dockerfile 来构建一个镜像。

2. **容器相关命令**：
   - `docker ps`: 列出所有正在运行的容器。
   - `docker ps -a`: 列出所有容器，包括已经停止的。
   - `docker run [OPTIONS] IMAGE [COMMAND] [ARG...]`: 创建并启动一个容器。
   - `docker start [CONTAINER_ID]`: 启动一个或多个已经被停止的容器。
   - `docker stop [CONTAINER_ID]`: 停止一个或多个正在运行的容器。
   - `docker restart [CONTAINER_ID]`: 重启一个或多个容器。
   - `docker rm [CONTAINER_ID]`: 删除一个或多个容器。
   - `docker exec -it [CONTAINER_ID] /bin/bash`: 进入一个正在运行的容器的终端。
   - `docker logs [CONTAINER_ID]`: 查看容器的日志输出。

3. **网络相关命令**:
   - `docker network ls`: 列出所有的网络。
   - `docker network create [NETWORK_NAME]`: 创建一个新的网络。
   - `docker network connect [NETWORK_NAME] [CONTAINER_ID]`: 将一个容器连接到一个网络。
   - `docker network disconnect [NETWORK_NAME] [CONTAINER_ID]`: 将一个容器从一个网络断开。

4. **卷(Volume)相关命令**:
   - `docker volume ls`: 列出所有的卷。
   - `docker volume create [VOLUME_NAME]`: 创建一个新的卷。
   - `docker volume rm [VOLUME_NAME]`: 删除一个卷。

5. **系统信息命令**:
   - `docker info`: 显示 Docker 系统信息，包括镜像和容器的数量。
   - `docker version`: 显示 Docker 的版本信息。

6. **其他有用命令**:
   - `docker-compose`: 是 Docker 的一个附属工具，用于定义和运行多容器的 Docker 应用。例如，使用 `docker-compose up` 来启动通过 `docker-compose.yml` 文件定义的服务。

这只是 Docker 常用命令的一部分，它的功能非常丰富，具体的命令和选项可以通过 `docker [COMMAND] --help` 来查看。