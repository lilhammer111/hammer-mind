# 安装

首先更新源

然后安装mysql服务器

`sudo apt install mysql-server`

# 配置

无密码登录：

`sudo mysql`

登录后，为了使外部程序（或者不使用sudo）登录mysql，需要做如下设置：

`ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'root';`



# 基础命令

## 登录

| 命令             | 说明       |
| ---------------- | ---------- |
| sudo mysql       | 无密码登录 |
| mysql -u root -p | 密码登录   |
|                  |            |

## 交互命令

进入交互模式的指令：

| 命令                                                         | 说明       | 案例                                                         |
| ------------------------------------------------------------ | ---------- | ------------------------------------------------------------ |
| show databases;                                              | 展示数据库 | 无                                                           |
| use <database>                                               | 选择数据库 | use tb_haha;                                                 |
| CREATE {DATABASE \| SCHEMA} [IF NOT EXISTS] db_name     <br />[create_option] ...  <br />create_option: [DEFAULT] {     <br />CHARACTER SET [=] charset_name   <br />\| COLLATE [=] collation_name   <br />\| ENCRYPTION [=] {'Y' \| 'N'} <br />} | 创建数据库 | create schema mxshop_user_srv character set utf8mb4 collate utf8mb4_general_ci; |

2