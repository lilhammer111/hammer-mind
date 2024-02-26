---
title: Reids note
date: 2023-07-29 14:55:20
categories: ["programming", "db", "redis"]
tags: ["redis"]
---

## 简介

### 测试命令

`redis-benchmark -q -n 10000`

### 对比其他服务器:

1. MySQL: 关系型数据库,慢
2. MongoDB: 键值对文档型数据库,但数据结构单一

### 应用场景

1. 缓存
2. 并发计数 -点赞/电商秒杀
3. 带有效期的验证码 
4. 实时排行榜
5. 生产者消费者模型

## 环境与准备

### 安装

1. reids- 用tab补全 看是否有redis -cli

2. ubuntu安装： `sudo apt-get install redis-server`

通过snap安装：

```
snap install redis
```

通过snap安装进入客户端命令不是`redis-cli`，而是

```
redis.cli
```



### 开启

`redis-server [配置文件] [-port port] [-slaveof host port]`

### 关闭

`redis-cli [-p port] shutdown`

### 登陆

登陆redis客户端

`redis-cli -h ip -p 6379 -a yourpwd  `

测试连接性

`ping`

若返回`pong`则说明连接成功



### 配置文件

位置

`/etc/redis/redis.conf`

要先备份

`cp /etc/redis/redis.conf{,.bak}`



### 设置密码

在配置文件中设置密码，500行

```redis.conf
requirepass yourpwd
```



### 重启redis服务器

`sudo /etc/init.d/redis-server restart`

若重启失败，说明配置文件有误

解决1：

终端执行：`redis-server /etc/redis/redis.conf`看报错，根据报错修改

解决2：

还原备份后的配置文件

```bash
sudo mv /etc/redis/redis.conf{,.error}
sudo mv /etc/redis/redis.conf.bak /etc/redis/redis.conf
```



### 客户端连接

`redis-cli -h ip -p 6379 -a yourpwd`

-h 和-p参数的默认值就是命令中的值

如果只输入`redis-cli`

会报错，但可以用`AUTH yourpwd`命令登陆



### 远程连接

1. 注释本地IP地址绑定

​		69行， `# bind 127.0.0.1 ::1`

1. 关闭保护模式

​		88行， `protected-mode no`

1. 重启服务



## 基础通用命令

redis有16个库，0-15, `select index`选择数据库，默认0库



`info [section]`

如，`info CPU`



`keys `查找所有符合的key

如，`keys *`，`keys h?llo`，`keys h*llo`



`type key`返回key的类型



`exists key`返回1代表存在



`del key`删除键值对



`rename key newkey`重命名



`flushdb`删除当前数据库数据

`flushall`删除所有数据库的数据



设置过期时间：

`expire[|pexpire] key second[|metersecond]`

删除过期时间：

`persist key`

返回0表示没有过期时间或者过期时间不存在

查看过期时间：

`ttl key`

返回-1表没有过期时间，-2代表当前key不存在

## 字符串

特点：

1. 字符串和数字都转成字符串存储
2. 二进制的方式存储在内存中

### 增改

设置或改变某个key的值

`set key value nx ex`

nx表示当不存在时才设置

ex表示过期时间，单位秒



批量添加：

`mset key1 value1 [key2 value2 ...]`



改某一段的值，相当于替换：

`setrange key offset value`

offset就是开始索引

### 删

参考基础通用命令



### 查

查看某个key的值

`get key`



批量查看：

`mget key1 [key2 ...]`



切片，包括start和end，从0开始：

`getrange key start end`



### 其他

获取某个key的值的长度：

`strlen key`



### 数值操作（必须掌握）

将 key 中储存的数字值增一或减一

`incr|decr key`

数字按步长增加：

`incrby key step`

数字按步长减少：

`decrby key step`

浮点数按步长增加，减少同理：

`incrbyfloat key step`



## 删除机制

惰性删除：

等调用key的时候，才检查这个键是否过期

定期删除：

在惰性删除的前提下，定期的主动删一下表，减少内存空间

- [ ] maxmemory



## 列表

特点：

1. 元素只能是字符串，不能是列表或者其他类型
2. 头尾删除快
3. 可重复
4. 最多2^32 - 1 个元素
5. 索引同python列表

### 增

头尾插入

`lpush key value [value...]`可以从左侧插入元素，返回list最新长度

src从右侧弹出，dst左侧插入

`rpoplpush src dst`

从某个位置插入

` linsert key after|before value newvalue`

### 删

`lpop key`

阻塞弹出（等待元素被添加进来）：

`blpop key timeout`，多个客户端删除，谁先执行谁先删，first in first



删除指定key中的值

`lrem key count value`

当count的正负决定顺逆，数值决定数量，为0则全部



只保留指定范围元素，其他全删

`ltrim key start stop`

 比如微博保留500条评论



### 改

`lset key index newvalue`



### 查

查询列表长度

`llen key`

查询列表指定范围内的值

`lrange key start stop`



## pyredis

### 安装

查看已安装的redis

`sudo pip3 freeze | grep redis`

没有安装的话，通过下面命令安装

`sudo pip3 install redis`

### 使用

1. 生成对象

   ``` python
   import redis
   r = redis.Redis(host='127.0.0.1', port=6379, db=0, password='123456')
   ```

2. 调用api

​		语法：`r.redis命令`



### 生产者消费者模型



## 位图操作

### 增改

`setbit key offset value`

```bash
127.0.0.1:6379> set mykey ab
OK
127.0.0.1:6379> setbit mykey -2 1
(error) ERR bit offset is not an integer or out of range
127.0.0.1:6379> setbit mykey 6 1
(integer) 0
127.0.0.1:6379> get mykey
"cb"
127.0.0.1:6379> setbit mykey 17 1
(integer) 0
127.0.0.1:6379> get mykey
"cb@"
```

### 查

`getbit key offset`

### 统计

统计某个key中1的数量

`bitcount key [start end]`

start和end是字节索引

官方说法：bitcount一次跟get key速度一样



## 散列表（哈希）

特点：

1. 不能嵌套，值的类型只能是string

优点：

1. 节省内存，但有前提：
   1. 字段小于512个
   2. value不超过64字节

2. 可直接获取key中某个字段的值，而嵌套的字典那种，必须取整个value

缺点：

1. 过期机制中，只能对key设置过期，对字段不行
2. 存储消耗大于字符串类型



### 增

设置某个key中的某个字段

`hset key field value`

只有当有key的时候才设置

`hsetnx key field value`



批量设置一个key中的多个字段

`hmset key field value [field value]`



### 查

查看字段值

`hget key field`

批量查看

`hmget key field [filed]`

查看所有的field

`hkeys key`

查看所有的值

`hvals key`

查看某个key的所有的字段和值

`hgetall key`



### 删

参考通用命令



### 数值操作

同字符串字符操作



### 其他

查看某个key的字段数

`hlen key`



### 哈希原理

python字典：哈希碰撞用开放地址法

redis： 哈希碰撞用单链法



## 集合

特点：

1. 无序，去重
2. 字符串类型，不能嵌套
3. 最多2^32 -1 个元素

**应用场景**

1. 共同好友

2. 纯随机抽奖

3. 防止元素重复

4. 黑/白名单



### 增

单个或批量增加

`sadd key member [member]`





### 删

删除一个或多个members

`srem key member [member]`



随机删除一个或多个member（弹出成员）

`spop key [count]`

### 查

查看key中所有members

`smembers key`



### 其他

查看member是否在key中

`sismember key member`

随机查看集合中指定个数的元素，默认为1

`srandmember key [count]`



查看集合中元素个数

`scard key`



把元素从源集合移动到目标集合

`smove source destination member`



取差集，把左边中含有右边的删掉

`sdiff key1 key2`

取差集并保存到目标集合

`sdiffstore destination key1 key2`

交集

`sinter key1 key2`

`sinterstore destination key1 key2`





并集

`sunion key1 key2`

`sunionstore destination key1 key2`



**查看底层结构**

`object encoding key`

集合在没有字符串的值的时候是哈希结构，但是全是数字的时候则是intset 数组结构



## 有序集合

特点：

1. 每个元素都有一个score，集合按照score排序



### 增

`zadd key score member`

### 删

删除成员

`zrem key member`

根据分数区间范围删除元素

`zremrangebyscore key min max`

### 改

增加或减少分值

`zincrby key increment member`

increment是增量，可为负

### 查

查看指定区间元素，按升序

`zrange key start stop [withscores]`

withscores是指带分数的

按降序

`zrerange key start stop [withscores]`



查看指定元素的分数

`zscore key member`

按升序查看指定元素的排名

`zrank key member`

降序

`zrevrank key member`



按照分数区间查看指定范围元素

`zrangebyscore key min max [withscores] [limit offset count]`

min/max是最小值最大值区间，默认闭区间，如果要开区间得在min前面加一个左圆括号（

limit选项和mysql一样

offset 跳过几个

count 返回几个



返回总元素数量

`zcard key`

返回指定区间元素个数

`zcount key min max`



### 其他

并集

` zunionstore destination numkeys key [key ... ] [WEIGHTS weight...][ aggregate sum|min|max] `

numkeys是说明一下做并集的key的数量

weight指定每个key的权重

aggregate指定相同key按照总和，最小值，最大值其中的哪个来算分



交集

`zinterstore destination numkeys key [key ...  ] [weights weight...] [aggregate sum|min|max]`



## 事务

四大特性ACID

1. 原子性
2. 一致性

3. 隔离性
4. 持久性



### 基本命令

开启事物

`MULTI`

执行命令

提交

`EXEC`

取消事物

`DISCARD`

注意：

1. 当语法错误时，可以回滚
2. 当执行的key不对时，则不回滚



乐观锁

`WATCH key`

WATCH导致的失败返回nil



### pipeline流水线

python操作事务需要依赖流水线技术（客户端技术）

```python
# 连接池
pool = redis.ConnectionPool(host='127.0.0.1', port=6379, db=0)
# 连接对象
r = redis.Redis(connection_pool=pool)
# 流水线
with r.pipeline(transaction=True) as p:
	p.multi()       
    p.incr("books")
    p.incr("books")
    p.execute()
```





## 数据持久化

### RDB

默认文件名：var/lib/redis/dump.rdb ，可修改，在配置文件/etc/redis/redis.conf中

```shell
# 表示rdb文件存放路径
dir /var/lib/redis 
# 文件名
dbfilename dump.rdb
```



命令

`SAVE`或`BGSAVE`

save的性质：

1. 执行save时redis会阻塞

2. rbd文件会被替换，全量替换

bgsave的性质：

1. 多线程，创建fork（）子进程，后台更新
2. 是否完成只能在/var/log/redis/redis-server.log中查看

```shell
 307 save 900 1  # 一般来说可以设置成半个小时一次
 308 save 300 10 # 表示距离上次save已经过去300秒，并且服务器数据库总共修改最少10次
 309 save 60 10000 
 # 上述三个条件满足其一就开启bgsave
```



### AOF

默认不开启

开启方式：

配置文件1094行中把no改为yes

`appendonly yes`

文件名

`appendfilename 'appendonly.aof'`

重启服务

`sudo /etc/init.d/redis-server restart` 这样重启了之后之前的数据都丢了，因为aof文件是空的



```bash
# appendfsync always
appendfsync everysec
# appendfsync no
```

重写aof文件

1. 用命令触发`BGREWRITEAOF`

2. 修改配置文件让服务器自动重写

​		`auto-aof ....`



## 主从复制

master能读能写，slaves只能读



**命令**

`redis-server --port <port> --slaveof <master-ip> <master-port> --masterauth <master-password>`

但这个是前台启动



配置文件启动

```bash
# redis_6380.conf

slaveof 127.0.0.1 6379
port 6380
daemonize yes
```



`redis-server redis_6380.conf`



客户端登陆

`redis-cli -p 6300`

切换主从关系

`slaveof IP PORT`

`slaveof no one`



**或者配置文件启动**



## 哨兵

### 安装

`sudo apt install redis-sentinel`

关闭服务？

`sudo /etc/init.d/redis-sentinel stop`



### 配置文件

拷贝原文件，然后修改新文件

```bash
# sentinel.conf
port 26379
sentinel monitor <master_name> 127.0.0.1 6379 <poll_number>
# 如果有密码需要添加该配置
sentinel auth-pass <master-name> <password>
sentinel down-after-milliseconds <master-name> <milliseconds>
```

