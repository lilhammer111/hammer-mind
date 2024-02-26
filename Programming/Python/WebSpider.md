---
title: Python 爬虫
date: 2023-07-29 14:55:20
categories: ["programming", "python", "爬虫"]
tags: ["爬虫", "python"]
---

# 爬虫介绍

## 爬虫分类

- 通用爬虫
- 聚焦爬虫
- 增量式爬虫

## 君子协议 /robots.txt

https://www.djangoproject.com/robots.txt



# http协议



## 常用请求头信息

- User-Agent
- Connection

## 常用响应头信息

- Content-Type

## https协议

安全的超文本传输协议

加密方式：

- 对称密钥加密
- 非对称密钥加密
- 证书秘钥加密

 

# 发送请求

## urllib

urllib是Python标准库之一，用于处理URL（Uniform Resource Locators，即统一资源定位符）的模块集合，包括了urllib.request、urllib.parse、urllib.error、urllib.robotparser等子模块，提供了许多对URL进行操作和处理的方法和函数。其中，urllib.request模块提供了打开和读取URL的方法，能够根据URL使用各种不同的传输协议进行网络请求，并返回响应内容；urllib.parse模块提供了URL解析方法，用于解析URL字符串并将其转化为一个具有更好可读性的数据格式等。 

### 常用API

| API名称                                                      | 作用                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `urllib.request.urlopen(url[, data[, timeout[, cafile[, capath[, cadefault[, context]]]]]])` | 打开并读取指定URL中的数据，**可传入一个url或者一个request对象**，返回一个响应对象。使用该对象调用read()方法读取响应内容，并使用`decode('utf-8')`转成中文。 |
| `urllib.request.urlretrieve(url[, filename[, reporthook[, data]]])` | 将指定URL的内容下载并保存到本地，file name是要保存的文件名，http.client.HTTPMessage对象包含服务器返回的信息。 |
| `urllib.request.Request(url,data,headers)`                   | 请求对象的定制                                               |
| `urllib.parse.quote(string, safe='/', encoding=None, errors=None)` | 将指定字符串中的非ASCII字符进行编码，并将其转换为URL编码格式。Safe参数指定另外不需要被编码的字符。 |
| `urllib.parse.urlencode(query, doseq=False, safe='', encoding=None, errors=None, quote_via=quote_plus)` | 将**指定的查询参数（query parameter）字典**转换为URL编码格式的字符串。将字典或元组形式的参数编码成URL查询字符串。可选的doseq参数如果设为True，则将重复的键构造为多个查询字符串参数。 |
| `urllib.request.install_opener(opener)`                      | 安装一个自定义的URL打开程序。                                |
| `urllib.request.build_opener([handler...])`                  | 创建和返回一个包含指定处理器（Handler）的Opener对象。        |
| `urllib.request.ProxyHandler(proxies=None)`                  | 构造函数，创建和返回一个处理代理的Handler对象。              |
| `urllib.request.HTTPBasicAuthHandler(password_mgr=None)`     | 构造函数，创建和返回一个处理基本认证的Handler对象。          |
| `urllib.request.HTTPCookieProcessor(cookiejar=None)`         | 构造函数，创建和返回一个处理HTTP cookies的Handler对象。      |

### 代码例子

```python
#使用ur111b来获取百度首页的源码
import urllib.request
#(1)定义一个Ur1
就是你要访问的地址
ur1 = 'http://www.baidu.com'
#(2)模拟浏览器向服务器发送请求response响应
response = urllib.request.urlopen(url)
#(3)获取响应中的页面的源码content内容的意思
#read方法返回的是字节形式的二进制数据
#我们要捋二进制的数据转换为字符串
#二进制--》字符串解码decode('编码的格式')》
content = response.read().decode('utf-8')
#(4)打印数据
print(content)
```



## requests模块

 概念：

使用：

- 指定url
- 发起请求
- 获取响应数据
- 写入本地文件



# 数据解析

## 正则表达式

| 规则   | 描述                                                         |
| ------ | ------------------------------------------------------------ |
| 字符   | 匹配指定字符                                                 |
| &#124; | 匹配多个模式之一                                             |
| .      | 匹配除了换行符之外的任意一个字符                             |
| ^      | 匹配字符串开头                                               |
| $      | 匹配字符串结尾                                               |
| *      | 匹配前面的字符可以出现0次、1次或多次                         |
| +      | 和星号很像，但是至少匹配1次                                  |
| ?      | 表示前面的字符可以出现0次或1次                               |
| {n}    | 匹配前面的字符恰好出现n次                                    |
| {n,}   | 匹配前面的字符出现n次或更多次                                |
| {n,m}  | 匹配前面的字符出现n到m次                                     |
| []     | 表示可选字符集之间的任意一个字符                             |
| [^...] | 表示不在可选字符集内                                         |
| \d     | 匹配任意数字字符，等价于[0-9]                                |
| \D     | 匹配任意非数字字符                                           |
| \s     | 匹配任意空白字符，包括空格、制表符和换行符                   |
| \S     | 匹配任意非空白字符                                           |
| \w     | 匹配字母、数字、下划线和汉字字符，等价于[a-zA-Z0-9_\u4e00-\u9fa5] |
| \W     | 匹配任意非字母、数字、下划线和汉字字符                       |
| ()     | 表示一个子表达式                                             |

 

## re模块

### 常用api方法

| API                                             | 功能                                                         |
| ----------------------------------------------- | ------------------------------------------------------------ |
| re.finditer(pattern, string, flags=0)           | 在字符串中查找所有匹配正则表达式的部分，**并返回一个迭代器，迭代器中的每个对象是一个 Match 对象。** |
| re.compile(pattern, flags=0)                    | 编译正则表达式并返回正则表达式对象，可以重复使用。           |
| re.match(pattern, string, flags=0)              | 从字符串的起始位置匹配正则表达式，如果匹配成功返回 Match 对象，否则返回 None。 |
| re.search(pattern, string, flags=0)             | 在字符串中查找第一个匹配的正则表达式，如果匹配成功则返回 Match 对象，否则返回 None。 |
| re.findall(pattern, string, flags=0)            | 在字符串中查找所有匹配的正则表达式，返回匹配结果的列表。     |
| re.sub(pattern, repl, string, count=0, flags=0) | 将字符串中所有匹配正则表达式的地方替换成指定的字符串。       |
| re.split(pattern, string, maxsplit=0, flags=0)  | 根据正则表达式将字符串拆分成多个子串，并返回一个列表。       |

### Match 对象

当使用 re 模块进行正则表达式匹配时，可以返回一个 Match 对象以获取更多有关匹配的信息。下面是整理的一个表格，其中包含了 match 对象的方法和属性。

| 方法             | 描述                                                         |
| ---------------- | ------------------------------------------------------------ |
| group()          | 按照子串的命名分组，返回被匹配到的对应子串。                 |
| start()          | 返回匹配子串在原字符串中的起始位置。                         |
| end()            | 返回匹配子串在原字符串中的结束位置。                         |
| span()           | 返回一个元组，元组中的两个数值分别表示匹配子串的起始位置和结束位置。 |
| groups()         | 返回一个元组，包含所有组的返回值（如果有的话）；默认第一个元素是整个字符串，之后的元素是用圆括号包含的子串。 |
| groupdict()      | 如果给出了命名组别，则该方法将返回一个字典，其中包含每个命名组别的名称和该组别的匹配子串。 |
| expand(template) | 将 template 中的转义字符替换为对应的组匹配值。template 中的反斜杠后面跟随一个数字可以将其转换为匹配值的序号。 |

Match 对象中的方法和属性可以帮助我们更加灵活地操作匹配结果，让我们能够实现更加复杂的文本处理任务。

### flags参数

在 re 模块中，flags 是一个可选参数，用于指定正则表达式的匹配模式。通过设置 flags 参数，可以改变正则表达式的行为，使其更加灵活和适应不同的文本匹配需求。flags 的取值以常量形式存在，可以使用按位或（|）运算符将多个值组合到一起。

下面是 flags 常量及其含义的简要介绍：

| 常量     | 含义                                                         |
| -------- | ------------------------------------------------------------ |
| re.I     | 忽略大小写匹配（即不区分大小写）。                           |
| re.M     | 多行模式匹配。                                               |
| re.S     | 使 .（点号）能够匹配包括换行符在内的所有字符。               |
| re.U     | 根据 Unicode 字符串处理正则表达式。                          |
| re.L     | 使 \w、\W、\b、\B、\d、\D、\s、\S 等元字符依赖于当前的语言环境，如默认情况下 \w 表示 `[A-Za-z0-9_]`，如果当前的语言环境是德语，那么它可能还包括一些额外的字符。 |
| re.X     | 允许使用注释。                                               |
| re.A     | ASCII 匹配模式，只匹配 ASCII 字符集。                        |
| re.DEBUG | 打开调试模式。                                               |

例如，如果需要实现一个正则表达式，可以忽略大小写进行匹配，可以在调用 re.compile() 函数时指定 flags 参数为 re.I，如下所示：

```python
import re

pattern = re.compile(r'hello', flags=re.I)
```

这样就会将正则表达式设置为忽略大小写的模式进行匹配。

### Pattern对象

Pattern 对象是 re 模块中用于匹配正则表达式的对象，提供了一系列方法和属性可以对文本进行匹配和替换等操作。下面是 Pattern 对象中常用的一些方法：

| 方法                                 | 描述                                                         |
| ------------------------------------ | ------------------------------------------------------------ |
| match(string, pos=0, endpos=None)    | 从字符串的起始位置开始查找匹配项，并返回一个匹配对象。pos 和 endpos 参数控制搜索范围。 |
| search(string, pos=0, endpos=None)   | 在字符串内查找匹配项，并返回一个匹配对象。pos 和 endpos 参数控制搜索范围。 |
| findall(string, pos=0, endpos=None)  | 查找所有符合正则表达式的子串，并返回一个列表。pos 和 endpos 参数控制搜索范围。 |
| finditer(string, pos=0, endpos=None) | 查找所有符合正则表达式的子串，并返回一个迭代器。pos 和 endpos 参数控制搜索范围。 |
| sub(repl, string, count=0)           | 将字符串中符合正则表达式的子串替换为指定的字符串，并返回替换后的新字符串。count 参数控制替换次数。 |
| split(string, maxsplit=0)            | 根据正则表达式将字符串分割成多个子串，并返回一个列表。maxsplit 参数控制最大分割次数。 |

除上述方法外，Pattern 对象还提供了以下几个用于获取信息的属性：

| 属性       | 描述                                                   |
| ---------- | ------------------------------------------------------ |
| pattern    | 返回编译后的正则表达式。                               |
| flags      | 返回编译后的正则表达式使用的标志。                     |
| groups     | 返回正则表达式中定义的所有组的数目。                   |
| groupindex | 返回一个字典，其中包含每个命名组别的名称和相应的组号。 |

上述方法和属性能够满足大多数正则表达式的需求，如果需要更加复杂的文本处理任务，还可以使用 re 模块提供的其他高级功能。
