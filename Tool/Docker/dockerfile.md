# 指令集

| Instruction                                                  | Description                                                 |
| :----------------------------------------------------------- | :---------------------------------------------------------- |
| [`ADD`](https://docs.docker.com/engine/reference/builder/#add) | Add local or remote files and directories.                  |
| [`ARG`](https://docs.docker.com/engine/reference/builder/#arg) | Use build-time variables.                                   |
| [`CMD`](https://docs.docker.com/engine/reference/builder/#cmd) | Specify default commands.                                   |
| [`COPY`](https://docs.docker.com/engine/reference/builder/#copy) | Copy files and directories.                                 |
| [`ENTRYPOINT`](https://docs.docker.com/engine/reference/builder/#entrypoint) | Specify default executable.                                 |
| [`ENV`](https://docs.docker.com/engine/reference/builder/#env) | Set environment variables.                                  |
| [`EXPOSE`](https://docs.docker.com/engine/reference/builder/#expose) | Describe which ports your application is listening on.      |
| [`FROM`](https://docs.docker.com/engine/reference/builder/#from) | Create a new build stage from a base image.                 |
| [`HEALTHCHECK`](https://docs.docker.com/engine/reference/builder/#healthcheck) | Check a container's health on startup.                      |
| [`LABEL`](https://docs.docker.com/engine/reference/builder/#label) | Add metadata to an image.                                   |
| [`MAINTAINER`](https://docs.docker.com/engine/reference/builder/#maintainer-deprecated) | Specify the author of an image.                             |
| [`ONBUILD`](https://docs.docker.com/engine/reference/builder/#onbuild) | Specify instructions for when the image is used in a build. |
| [`RUN`](https://docs.docker.com/engine/reference/builder/#run) | Execute build commands.                                     |
| [`SHELL`](https://docs.docker.com/engine/reference/builder/#shell) | Set the default shell of an image.                          |
| [`STOPSIGNAL`](https://docs.docker.com/engine/reference/builder/#stopsignal) | Specify the system call signal for exiting a container.     |
| [`USER`](https://docs.docker.com/engine/reference/builder/#user) | Set user and group ID.                                      |
| [`VOLUME`](https://docs.docker.com/engine/reference/builder/#volume) | Create volume mounts.                                       |
| [`WORKDIR`](https://docs.docker.com/engine/reference/builder/#workdir) | Change working directory.                                   |

ADD和COPY区别就是，ADD拷贝压缩包到容器中时，会自动解压，COPY不会。

> 刚才脑子短路了，突然在想这些指令到底是在宿主机执行还是在容器中执行的了。
>
> 实际上这个问题很好理解，无论是Dockerfile中的`RUN git clone ...`命令，还是什么拷贝文件的命令，这些资源一定是构建镜像的时候就已经打包到镜像里的了，否则当我使用镜像实例一个容器的时候，难不成到那个时候才开始获取这些资源？万一这些资源没了，那我的容器就构建失败了？显然不合理。