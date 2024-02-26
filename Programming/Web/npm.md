## npm简介

npm是node包管理器，超过100万个软件包，世界最大的软件注册表

**官网**

https://www.npmjs.com



## 基础

### 帮助

`npm help <command>`

### 安装

`sudo snap install node`

### 查看镜像源

`npm config get registry`

### 更换镜像源

`npm config set registry https://registry.npm.taobao.org`

### 查看软件包可安装的版本

`npm view <module_name> versions`

### 查看已安装软件包的版本

`npm list <module_name>`

或者 `<module_name> -v`

### 更新

`npm update <module_name>`

### 卸载

`npm uninstall <module_name>`



> **Tips：**
>
> 当我把node_modules中的安装包全删了时，只要我的package.json配置项中有依赖，我可以直接使用`npm install`命令就能直接安装所有的依赖



### 生成配置文件

`npm create [|init] [-y]`