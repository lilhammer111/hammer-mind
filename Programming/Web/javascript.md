## 语法和基本数据类型：

JavaScript 的语法和基本数据类型包括变量、操作符、条件语句、循环语句、函数等。

## DOM 操作

DOM (文档对象模型) 是 JavaScript 中用来访问和操作网页内容的一种 API。开发者可以使用 JavaScript 来访问和修改 HTML 元素及其属性、内容等。

DOM树

文档——document

元素——element

节点——node

### 获取元素

在JavaScript中，可以使用DOM (文档对象模型)来获取HTML元素。常用的方法有以下几种：

1. 通过ID获取元素

可以使用 `document.getElementById()` 方法来获取具有指定ID的元素。例如：

```javascript
let element = document.getElementById("myElement");
```

上面的代码将会获取具有ID为"myElement"的元素，并将其存储在变量`element`中。

2. 通过标签名获取元素

可以使用 `document.getElementsByTagName()` 方法来获取具有指定标签名的所有元素。例如：

```javascript
let elements = document.getElementsByTagName("p");
```

上面的代码将会获取所有`<p>`元素，并将其存储在变量`elements`中。

3. 通过类名获取元素

可以使用 `document.getElementsByClassName()` 方法来获取具有指定类名的所有元素。例如：

```javascript
let elements = document.getElementsByClassName("myClass");
```

上面的代码将会获取具有类名为"myClass"的所有元素，并将其存储在变量`elements`中。

4. 通过选择器获取元素

可以使用 `document.querySelector()` 方法或 `document.querySelectorAll()` 方法来获取具有指定CSS选择器的元素。例如：

```javascript
let element = document.querySelector("#myElement");
let elements = document.querySelectorAll(".myClass");
```

上面的代码将会分别获取具有ID为"myElement"和类名为"myClass"的所有元素，并将其存储在变量`element`和`elements`中。

这些是获取HTML元素的一些基本方法，还有很多其他方法可以使用。

### 事件基础

### 操作元素

### 节点操作



## 事件处理

JavaScript 可以通过监听 DOM 元素上的事件来响应用户的交互行为，如点击、滚动、鼠标移动等。

## Ajax 技术：

Ajax (Asynchronous JavaScript and XML) 是一种使用 JavaScript、XML 和 HTTP 请求与服务器进行通信的技术，常用于实现无需刷新页面的异步数据交互。

## 函数式编程：

JavaScript 支持函数式编程，开发者可以使用函数作为参数或返回值，将函数作为一等公民来处理数据和逻辑。

## 面向对象编程

相对于传统的基于类的面向对象编程，JavaScript 支持基于原型的面向对象编程，开发者可以通过构造函数和原型链来实现继承和多态等概念。

## ES6 新特性

ES6 引入了许多新特性，如箭头函数、解构赋值、let 和 const 关键字、模板字符串、Promise 等。

## 模块化

JavaScript 支持模块化编程，通过 import 和 export 关键字来实现代码的可重用和组织。