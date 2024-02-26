# Vue2

## Vue简介

Vue是一个流行的前端JavaScript框架，用于构建用户界面和单页应用程序。它由Evan You于2014年创建，自那以后在开发者中获得了很大的关注。

Vue提供了一个简单而灵活的架构，使开发人员可以轻松地创建复杂的Web应用程序。它以易用性、轻量级和优秀的文档闻名。Vue.js的一些关键特性包括其反应式数据绑定、基于组件的结构和模板语法。Vue也提供了许多有用的功能，如内置的路由器和状态管理库，可以帮助开发人员构建更加丰富和复杂的应用程序。

总之，Vue是一个功能强大、易于学习和使用的前端框架，适用于各种规模的项目和应用程序。

> 为什么说Vue是渐进式框架？

Vue被称为渐进式框架，因为它的核心库是非常精简的，只关注于视图层（View Layer），同时它也提供了一系列的插件和库，可以根据实际需求进行选择和集成。这意味着开发人员可以逐步采用Vue，而不必全盘接受其所有功能。

具体来说，Vue的渐进式特性包括以下方面：

1. 核心库：Vue.js的核心库非常小巧，只关注于视图层，可以与其他库或框架配合使用，如jQuery等。
2. 组件系统：Vue采用组件化开发模式，使得代码更加模块化、可复用，并且易于维护和测试。
3. 插件：Vue提供了许多插件，如路由器、状态管理库等，可以根据需要进行选择和集成。
4. 非侵入性：Vue的设计非常灵活，可以与现有的项目或代码库进行整合，不会对原有的代码结构造成影响。
5. 逐步采用：你可以循序渐进地采用Vue，只需将其用作一个简单的替代品，然后再逐步引入更多的功能和特性。

综上所述，Vue被称为渐进式框架，是因为它允许开发人员根据实际需求使用不同的功能和插件，同时保持代码库可维护性和可扩展性。

### 特点

1. 组件化开发
2. 声明式编码
3. 虚拟DOM和Diff算法

### JS前置知识

1. ES6语法规范
2. ES6模块化
3. 包管理器
4. 原型，原型链
5. 数组常用方法
6. axios
7. promise

### 官网

https://vuejs.org/

中文官网：https://cn.vuejs.org/

文档：https://cn.vuejs.org/guide/introduction.html

## 工具

### 脚手架 Vue CLI

### IDE

推荐使用的 IDE 是 [VSCode](https://code.visualstudio.com/)，配合 [Vue 语言特性 (Volar)](https://marketplace.visualstudio.com/items?itemName=Vue.volar) 插件。该插件提供了语法高亮、TypeScript 支持，以及模板内表达式与组件 props 的智能提示。

> Volar 取代了我们之前为 Vue 2 提供的官方 VSCode 扩展 [Vetur](https://marketplace.visualstudio.com/items?itemName=octref.vetur)。如果你之前已经安装了 Vetur，请确保在 Vue 3 的项目中禁用它。

使用Vue CLI非常简单，只需遵循以下步骤：

1. 首先需要安装Node.js和npm。你可以从官方网站下载最新版本的Node.js，并随之自动安装npm。

2. 打开终端或命令行窗口，运行以下命令来安装Vue CLI：

   ```powershell
   npm install -g @vue/cli
   ```

3. 安装完成后，你可以使用以下命令来创建一个新的Vue项目：

   ```powershell
   vue create my-project
   ```

   其中 `my-project` 是你要创建的项目名称。执行此命令后，Vue CLI会提示你选择一些配置选项，例如应用程序特性、插件和预设等。

4. 安装完毕后，进入到新建的项目目录，然后使用以下命令启动开发服务器：

   ```powershell
   cd my-project
   npm run serve
   ```

   这将启动一个本地开发服务器，你可以在浏览器中访问 [http://localhost:8080](http://localhost:8080) 来查看你的应用程序。同时，Vue CLI 也提供了其他命令，例如打包、测试等。

以上就是使用Vue CLI创建和运行一个新的Vue.js项目所需的基本步骤。

### 浏览器开发者插件 

Vue 的浏览器开发者插件使我们可以浏览一个 Vue 应用的组件树，查看各个组件的状态，追踪状态管理的事件，还可以进行组件性能分析。

## 模板语法 v-

Vue.js 的模板语法可以分为以下几类：

1. **插值：**使用双大括号或 v-bind 指令进行数据绑定。常用于渲染文本或绑定 HTML 属性。

```html
<div>{{ message }}</div>
<img v-bind:src="imageUrl" />
```

2. **指令：**Vue.js 提供了一些内置指令，如 v-if、v-for、v-on 等，可以添加在元素上完成特定的功能。

```html
<div v-if="isVisible">Visible</div>
<ul>
  <li v-for="(item, index) in items" :key="index">{{ item }}</li>
</ul>
<button v-on:click="handleClick">Click me</button>
```

3. **缩写：**Vue.js 提供了一些缩写，使得模板更加简洁易读，例如 v-bind 可以缩写为 ":"，v-on 可以缩写为 "@"。

```html
<img :src="imageUrl" />
<button @click="handleClick">Click me</button>
```

4. **过滤器：**Vue.js 的过滤器可以对文本格式化处理，并在插值表达式中使用。

```html
<div>{{ message | capitalize }}</div>
```

5. **计算属性：**Vue.js 的计算属性可以对数据进行复杂的计算，并返回计算结果。

```html
<div>{{ reversedMessage }}</div>
```

6. **监听器：**Vue.js 提供了 watch 选项来监听数据变化，从而执行一些逻辑操作。

```html
<div>{{ message }}</div>
```

这些模板语法可以组合使用，从而实现更加复杂的功能。在 Vue.js 中，模板语法非常灵活，开发者可以根据实际需求选择最适合的方式来实现功能。

### 插值语法

Vue.js 提供了以下三种插值语法：

1. **双大括号插值（Mustache 语法）：**使用两个大括号包裹表达式，将其渲染为文本内容。

```html
<span>{{ message }}</span>
```

2. **单大括号插值（v-once 指令）：**和双大括号类似，但是只会渲染一次。常用于静态内容的优化。

```html
<span v-once>{{ staticMessage }}</span>
```

需要注意的是，双大括号插值和单大括号插值不能用于 HTML 属性上。

### 指令语法

Vue.js 提供了很多指令，以下是一些常用的指令：

#### v-if , v-else-if 和 v-else

根据表达式的值的真假条件地渲染元素或组件。

```html
<div v-if="isVisible">Visible</div>
```

##### 条件渲染

#### v-for

根据数据源渲染列表，可以使用带括号的语法指定当前项和索引。

```html
<ul>
  <li v-for="(item, index) in items" :key="index">{{ item }}</li>
</ul>
```

##### 列表渲染

##### 列表过滤

#### v-bind

动态地绑定一个或多个 HTML 属性。可以缩写为 ":"。

```html
<button v-bind:disabled="isDisabled">Click me</button>
<!-- 缩写 -->
<button :disabled="isDisabled">Click me</button>
```

##### 绑定class样式

1. 字符串写法
2. 数组写法
3. 对象写法

```vue
<template>
  <div :class="classObject"></div>
</template>

<script>
export default {
  data() {
    return {
      isActive: true,
      hasError: false
    }
  },
  computed: {
    classObject() {
      return {
        active: this.isActive,
        'text-danger': this.hasError
      }
    }
  }
}
</script>
```


#### v-on

绑定事件监听器，可以使用 "@" 缩写。

```html
<button v-on:click="handleClick">Click me</button>
<!-- 缩写 -->
<button @click="handleClick">Click me</button>
```

#### v-model

双向数据绑定，把表单元素的值与 Vue 实例中的数据进行绑定。

```html
<input v-model:value="message" />
<!-- 缩写 -->
<input v-model="message" />
```

#### v-show:

根据表达式的值的真假条件地切换元素的可见性，与 v-if 不同的是，v-show 只是将元素的样式 display 设为 none。

```html
<div v-show="isVisible">Visible</div>
```

这些都是 Vue.js 常用的指令，Vue.js 还有其他一些指令如 v-cloak、v-pre、v-html 等，更多关于 Vue.js 指令的内容请参考官方文档。

## 数据代理 data

### `object.defineProperty`

`Object.defineProperty()` 是 JavaScript 中用于定义对象属性的方法。它允许开发者定义新属性或修改现有属性，并且可以控制这些属性的行为。

`Object.defineProperty()` 方法需要三个参数：要定义属性的对象，要定义或修改的属性名称以及一个描述该属性特征的对象。描述符对象包括以下可选属性：

- `value`：属性的值
- `writable`：属性是否可写入
- `enumerable`：属性是否可枚举
- `configurable`：属性是否可被删除或更改特征

对于更高级的用途，**描述符对象**还可以包含 getter 和 setter 函数，以及设置多个属性的方法 (`Object.defineProperties()`)。

> **什么是描述符对象呢？**

以下是一个使用 `Object.defineProperty()` 方法定义属性的例子：

```javascript
const obj = {};

Object.defineProperty(obj, 'name', {
  value: 'John',
  writable: false,
  enumerable: true,
  configurable: false
});

console.log(obj.name); // 输出 "John"
obj.name = 'Jane';     // 尝试修改属性值，但因为 writable 属性设置为 false，所以失败
console.log(obj.name); // 输出 "John"

for (let key in obj) {
  console.log(key);   // 因为 enumerable 属性设置为 true，所以 name 属性会被枚举出来
}
```

在这个例子中，我们首先创建了一个空对象 `obj`，然后使用 `Object.defineProperty()` 方法定义了一个名为 `name` 的新属性，并将其值设为 `'John'`。我们还通过设置 `writable` 和 `configurable` 属性来限制了该属性的可写和可删除性。最后，我们打印了 `obj.name` 的值，并尝试修改它，但修改操作失败了，因为我们在描述符对象中将 `writable` 属性设置为 `false`。

另外，我们使用 for...in 循环遍历了 `obj` 对象的所有属性，由于我们在描述符对象中将 `enumerable` 属性设置为 `true`，因此 `name` 属性也被枚举了出来。

> **描述符对象更高级的用途怎么使用？有没有例子？**

描述符对象还有一些高级用法，比如使用 getter 和 setter 函数来实现属性的访问器方法。下面是一个使用 getter 和 setter 函数的例子：

```javascript
const obj = {
  firstName: 'John',
  lastName: 'Doe'
};

Object.defineProperty(obj, 'fullName', {
  get: function() {
    return this.firstName + ' ' + this.lastName;
  },
  set: function(value) {
    const parts = value.split(' ');
    this.firstName = parts[0];
    this.lastName = parts[1];
  }
});

console.log(obj.fullName);   // 输出 "John Doe"

obj.fullName = 'Jane Smith';
console.log(obj.firstName);  // 输出 "Jane"
console.log(obj.lastName);   // 输出 "Smith"
```

在这个例子中，我们首先创建了一个包含 `firstName` 和 `lastName` 属性的对象 `obj`。然后，我们使用 `Object.defineProperty()` 方法来定义一个名为 `fullName` 的新属性，并分别设置了 getter 和 setter 函数。

getter 函数返回 `firstName` 和 `lastName` 属性的组合字符串，而 setter 函数接受一个字符串参数，并将它拆分成两个部分，然后将其分别赋值给 `firstName` 和 `lastName` 属性。

最后，我们打印了 `obj.fullName` 的值，并且通过给 `obj.fullName` 赋值来测试了 setter 函数的行为，验证了其是否成功地更新了 `firstName` 和 `lastName` 属性的值。

需要注意的是，在使用 getter 和 setter 函数时，描述符对象中不能同时设置 `value` 和 `writable` 属性。

### vue中数据代理应用

## 计算属性 computed

### 定义

在 Vue 的实例中，我们可以通过在 `computed` 选项中定义计算属性来创建一个新的响应式属性。计算属性本质上就是一个带有 getter 和 setter 方法的属性，用于根据其他已定义的属性动态计算出一个新的值。例如：

```js
new Vue({
  data: {
    firstName: 'John',
    lastName: 'Doe'
  },
  computed: {
    fullName: function () {
      return this.firstName + ' ' + this.lastName
    }
  }
})
```

在上面的代码中，我们定义了一个计算属性 `fullName`，它由 `firstName` 和 `lastName` 这两个属性动态计算而来。这里的 getter 函数返回了计算结果，setter 函数 (如果定义了) 则用于处理计算属性的变化。

### 使用方法

1. 计算属性的基本用法

在 Vue 中，我们可以使用计算属性来处理一些复杂的逻辑并将其封装成一个新的响应式属性。例如，假设我们需要根据用户的输入动态计算出一个新的字符串，可以使用如下代码：

HTML：

```vue
<div>
  <input v-model="firstName" placeholder="请输入名字">
  <input v-model="lastName" placeholder="请输入姓氏">
  <p>您好，{{ fullName }}！</p>
</div>
```

JavaScript：

```js
new Vue({
  el: '#app',
  data: {
    firstName: '',
    lastName: ''
  },
    // 简写
  computed: {
    fullName () {
      return this.firstName + ' ' + this.lastName
    }
  }
    // 完整写法
    /*
    computed: {
  		fullName: {
    		get: function() {
      			return this.firstName + ' ' + this.lastName;
   			},
    		set: function(value) {
      			var names = value.split(' ');
      			this.firstName = names[0];
      			this.lastName = names[names.length - 1];
    		}
  		}
	}*/
})
```

在上面的代码中，我们定义了两个输入框和一个计算属性 `fullName`，它由 `firstName` 和 `lastName` 这两个属性动态计算而来。当用户在输入框中输入内容时，计算属性会自动更新并显示新的值。

2. 计算属性的缓存机制

计算属性具有缓存机制，它会将计算过的结果缓存起来，在下一次访问该属性时直接返回缓存的计算结果，而不是重新计算。这样可以避免重复计算和浪费资源。

HTML：

```vue
<div>
  <button @click="increment">增加</button>
  <p>当前计数：{{ count }}</p>
  <p>计算结果：{{ result }}</p>
</div>
```

JavaScript：

```js
new Vue({
  el: '#app',
  data: {
    count: 0
  },
  computed: {
    result: function () {
      console.log('正在计算结果...')
      return this.count * 2
    }
  },
  methods: {
    increment: function () {
      this.count++
    }
  }
})
```

在上面的代码中，我们定义了一个计算属性 `result`，它由 `count` 这个属性动态计算而来。当我们点击“增加”按钮时，`count` 属性会自增，并且 `result` 属性会自动更新并显示新的值。由于计算属性具有缓存机制，所以每次只会在第一次访问时计算结果，之后再次访问时会直接返回缓存的结果，从而避免重复计算。

3. 计算属性和侦听器的区别

Vue 中除了计算属性外，还有另一种处理复杂逻辑的方式——侦听器 (watcher)。与计算属性不同的是，侦听器不会返回任何值，它只是在侦听的数据改变时执行某些操作。

HTML：

```html
<div>
  <input v-model="firstName" placeholder="请输入名字">
  <input v-model="lastName" placeholder="请输入姓氏">
  <p>您好，{{ fullName }}！</p>
</div>
```

JavaScript：

```js
new Vue({
  el: '#app',
  data: {
    firstName: '',
    lastName: '',
    fullName: ''
  },
  watch: {
    firstName: function (val) {
      this.fullName = val + ' ' + this.lastName
    },
    lastName: function (val) {
      this.fullName = this.firstName + ' ' + val
    }
  }
})
```

在上面的代码中，我们使用了侦听器来监听 `firstName` 和 `lastName` 这两个属性的变化，并更新计算属性 `fullName`。如果某个属性发生变化，那么 `watcher` 中对应的函数就会被调用，并传入新值。在这个例子中，我们分别监听了 `firstName` 和 `lastName` 这两个属性的变化，并根据它们的值动态计算出 `fullName` 属性的新值。

需要注意的是，计算属性和侦听器

### 特点

计算属性有以下几个特点：

- 计算属性是响应式的：当其所依赖的数据发生变化时，计算属性会自动重新计算并更新。
- 计算属性是惰性求值的：只有在被访问时才会进行计算，而且在同一个实例中多次访问同一个计算属性时，只会计算一次。
- 计算属性具有缓存机制：如果一个计算属性已经被计算过了，那么 Vue 会将其缓存起来，在下一次访问该属性时直接返回缓存的计算结果，而不是重新计算。这样可以避免重复计算和浪费资源。
- 计算属性可以依赖其他计算属性：如果一个计算属性依赖于其他计算属性，那么当其所依赖的计算属性发生变化时，它也会自动重新计算并更新。

### 注意事项

在使用计算属性时，需要注意以下几点：

- 计算属性不应该有副作用，即不应该修改其他属性或进行其他可能会影响系统状态的操作。
- 计算属性的 getter 函数应该是纯函数，即相同的输入始终产生相同的输出。
- 如果某个计算属性的 getter 函数很耗时，那么可以考虑使用缓存机制来优化性能。
- 计算属性只会在其所依赖的数据发生变化时才重新计算，因此在定义计算属性时要确保其所依赖的数据是响应式的。如果某个计算属性依赖于一个非响应式的数据，则其无法正确地更新。

## 监视属性 watch

### 基础用法

Vue 提供了一个 `watch` 选项来实现监视属性。在组件的 `watch` 选项中，我们可以定义一个与待监听属性同名的方法。当该属性发生变化时，就会触发这个方法，并传递新值和旧值两个参数。例如：

```vue
<template>
  <div>
    <input type="text" v-model="message">
  </div>
</template>

<script>
export default {
  data() {
    return {
      message: 'Hello, world!',
    };
  },
  watch: {
    message(newValue, oldValue) {
      console.log(`Message changed from "${oldValue}" to "${newValue}"`);
    },
  },
};
</script>
```

在上述代码中，当输入框的值发生变化时，控制台会输出类似于 "Message changed from "Hello, world!" to "Hi, there!"" 的信息。

### 深度监听

有时候我们需要监听对象内部属性的变化，这时我们可以将 `watch` 选项中的对象改为函数，并将 `deep` 属性设置为 `true`。例如：

```vue
<template>
  <div>
    <input type="text" v-model="user.name">
  </div>
</template>

<script>
export default {
  data() {
    return {
      user: {
        name: 'John',
        age: 30,
      },
    };
  },
  watch: {
    user: {
      handler(newValue, oldValue) {
        console.log(`User changed from "${oldValue}" to "${newValue}"`);
      },
      deep: true,
    },
  },
};
</script>
```

在上述代码中，当 `user` 对象内部的 `name` 属性发生变化时，控制台会输出类似于 "User changed from "{ name: 'John', age: 30 }" to "{ name: 'Jane', age: 30 }"" 的信息。

### 立即执行

如果我们需要在组件创建后立即执行监听属性的回调函数，可以使用 `immediate` 属性。例如：

```vue
<template>
  <div>
    <input type="text" v-model="count">
  </div>
</template>

<script>
export default {
  data() {
    return {
      count: 0,
    };
  },
  watch: {
    count: {
      immediate: true,
      handler(newValue, oldValue) {
        console.log(`Count changed from "${oldValue}" to "${newValue}"`);
      },
    },
  },
};
</script>
```

在上述代码中，当组件创建后，会立即执行 `count` 属性的回调函数，并输出类似于 "Count changed from "0" to "0"" 的信息。

### 应用场景

1. 异步操作

当我们需要在组件加载完成后，执行异步操作并根据结果更新页面时，可以使用监视属性来监听数据变化并触发更新。例如，我们可以监听一个对象的属性变化，然后在回调函数中执行异步调用，并将返回结果赋值给组件的另一个属性，从而实现页面的动态更新。

```vue
<template>
  <div>
    <p>{{ result }}</p>
    <button @click="fetchData">Fetch Data</button>
  </div>
</template>

<script>
export default {
  data() {
    return {
      data: {},
      result: null,
    };
  },
  watch: {
    data(newValue, oldValue) {
      this.fetchResult();
    }
  },
  methods: {
    async fetchData() {
      const response = await fetch('https://some-api.com/data');
      this.data = await response.json();
    },
    fetchResult() {
      this.result = /* some calculation using this.data */;
    },
  },
};
</script>
```

在上述代码中，当 `data` 对象发生变化时，会触发回调函数 `fetchResult()` 来重新计算 `result` 属性的值。

2. 表单验证

当我们需要对一个表单进行验证时，可以使用监视属性来监听表单数据的变化并进行相应的验证。例如，我们可以监听表单输入框的值变化，然后在回调函数中执行验证操作，并将验证结果保存到组件的另一个属性中，从而实现表单的动态验证。

```vue
<template>
  <div>
    <label>Username:</label>
    <input type="text" v-model="username">
    <p v-if="!isValid">Username should be at least 3 characters long.</p>
  </div>
</template>

<script>
export default {
  data() {
    return {
      username: '',
      isValid: true,
    };
  },
  watch: {
    username(newValue, oldValue) {
      this.validateUsername();
    }
  },
  methods: {
    validateUsername() {
      if (this.username.length < 3) {
        this.isValid = false;
      } else {
        this.isValid = true;
      }
    },
  },
};
</script>
```

在上述代码中，当输入框的值发生变化时，会触发回调函数 `validateUsername()` 来对输入框的值进行验证，并根据验证结果更新 `isValid` 属性的值。如果输入的用户名长度小于 3 ，则会显示一条提示信息。

3. 计算属性的实现

有时候我们需要根据其他属性的值动态计算出一个新的属性值，这时可以使用计算属性来实现。而计算属性本质上就是一个带有监视属性的函数。例如，我们可以监听多个属性的变化，并根据它们的值计算出一个新的属性值，供其他组件使用。

```vue
<template>
  <div>
    <p>Total price: {{ totalPrice }}</p>
  </div>
</template>

<script>
export default {
  data() {
    return {
      price: 5,
      quantity: 2,
    };
  },
  watch: {
    price(newValue, oldValue) {
      this.getTotalPrice();
    },
    quantity(newValue, oldValue) {
      this.getTotalPrice();
    }
  },
  computed: {
    totalPrice() {
      return this.price * this.quantity;
    },
  },
  methods: {
    getTotalPrice() {
      this.totalPrice = this.price * this.quantity;
    },
  },
};
</script>
```

在上述代码中，当 `price` 或 `quantity` 属性发生变化时，会触发回调函数 `getTotalPrice()` 来重新计算 `totalPrice` 计算属性的值，并更新到模板中展示。

4. 组件通信

当需要在父组件和子组件之间传递数据时，可以使用 prop 和 emit 进行通信。但是如果涉及到数据变化时需要做出相应的响应，就需要使用监视属性来监听数据变化并执行相应的操作。例如，我们可以在父组件中监听子组件传递过来的数据，并在回调函数中执行相应的操作。

```vue
<!-- Parent.vue -->
<template>
  <div>
    <child :data="myData" @change="handleChange"></child>
  </div>
</template>

<script>
import Child from './Child.vue';

export default {
  components: {
    Child,
  },
  data() {
    return {
      myData: {},
    };
  },
  methods: {
    handleChange(newValue, oldValue) {
      // do something with the changed data
    },
  },
};
</script>

<!-- Child.vue -->
<template>
  <div>
    <input type="text" v-model="data.name">
  </div>
</template>

<script>
export default {
  props: ['data'],
  watch: {
    data(newValue, oldValue) {
      this.$emit('change', newValue, oldValue);
    }
  },
};
</script>
```

在上述代码中，当 `Child` 组件传递过来的 `data` 属性发生变化时，会触发父组件的回调函数 `handleChange()` 来处理数据变化后的操作。子组件可以通过 `$emit` 方法通知父组件数据的变化。

以上就是 Vue 监视属性的详细知识点和应用场景，希望对你有所帮助！



## 条件渲染 `v-if/v-show`

## 列表渲染 `v-for`

### 维护状态

## 事件处理 `v-on: / @`

### 事件类型

在Vue.js中，有以下几种事件：

1. 生命周期钩子事件：Vue组件有多个生命周期钩子，可以让我们在组件不同阶段执行自定义逻辑。常用的生命周期钩子事件包括`created`、`mounted`、`updated`和`destroyed`等。

2. 自定义事件：除了内置的生命周期钩子事件外，Vue还支持自定义事件，可以让父组件向子组件传递数据，或者允许子组件向父组件发送通知。我们可以通过`$emit()`方法在父组件中触发自定义事件，在子组件中使用`$on()`方法监听该事件。

3. 原生DOM事件：在Vue中也可以绑定HTML DOM事件，例如`click`、`keydown`、`resize`等。可以使用`v-on`指令来绑定HTML DOM事件，并使用JavaScript代码处理事件。

下面是一些具体的例子：

1. 生命周期钩子事件

```vue
<template>
  <div>{{ message }}</div>
</template>

<script>
export default {
  data() {
    return {
      message: 'Hello World!'
    };
  },
  created() {
    console.log('Component created');
  },
  mounted() {
    console.log('Component mounted');
  },
  updated() {
    console.log('Component updated');
  },
  destroyed() {
    console.log('Component destroyed');
  }
};
</script>
```

在这个例子中，我们定义了一个Vue组件，并实现了`created`、`mounted`、`updated`和`destroyed`等生命周期钩子事件。当Vue实例创建、挂载、更新和销毁时，这些生命周期钩子就会被调用。

2. 自定义事件

```vue
<template>
  <child-component @greet="onGreet"></child-component>
</template>

<script>
import ChildComponent from './ChildComponent.vue';

export default {
  components: {
    ChildComponent
  },
  methods: {
    onGreet(message) {
      console.log(message);
    }
  }
};
</script>
```

在这个例子中，我们在父组件中向`child-component`组件派发一个名为`greet`的自定义事件，并在父组件中使用`@greet`监听该事件。当子组件触发`greet`事件时，父组件中的`onGreet()`方法将被调用。

3. 原生DOM事件

| 事件名称  | 描述                             |
| --------- | -------------------------------- |
| click     | 当用户单击一个元素时触发。       |
| dblclick  | 当用户双击一个元素时触发。       |
| mouseover | 当鼠标移动到一个元素上方时触发。 |
| mouseout  | 当鼠标从一个元素移出时触发。     |
| mousedown | 当用户按下鼠标按钮时触发。       |
| mouseup   | 当用户释放鼠标按钮时触发。       |
| keydown   | 当用户按下一个键盘键时触发。     |
| keyup     | 当用户释放一个键盘键时触发。     |
| focus     | 当一个元素获取焦点时触发。       |
| blur      | 当一个元素失去焦点时触发。       |
| load      | 当文档或图像加载完成时触发。     |
| unload    | 当文档或图像卸载完成时触发。     |
| resize    | 当浏览器窗口大小改变时触发。     |
| scroll    | 当用户滚动某个元素时触发。       |

例子：

```vue
<template>
  <button @click="onClick">Click me</button>
</template>

<script>
export default {
  methods: {
    onClick() {
      console.log('Button clicked'); // 输出Button clicked
    }
  }
};
</script>
```

在这个例子中，我们在按钮上绑定了一个`click`事件，并在该事件触发时调用了`onClick()`方法。当用户单击按钮时，控制台将打印出`Button clicked`。

### 事件修饰符

Vue中的事件修饰符用于修改事件的行为，例如阻止默认行为、阻止单击事件冒泡等。Vue提供了以下几个常用的事件修饰符：

1. `.stop`

  `.stop`可以用来停止事件向父元素的传播。

  ```html
  <template>
    <div @click="handleParentClick">
      <button @click.stop="handleChildClick">点击我</button>
    </div>
  </template>

  <script>
  export default {
    methods: {
      handleChildClick() {
        console.log('子元素被点击了')
      },
      handleParentClick() {
        console.log('父元素被点击了')
      }
    }
  }
  </script>
  ```

  上述代码中，我们在按钮上使用`.stop`修饰符来停止事件向父元素传播。因此，当你点击按钮时，只会触发`handleChildClick`方法，而不会触发`handleParentClick`方法。

2. `.prevent`

  `.prevent`可以用来阻止默认行为。

  ```html
  <template>
    <form @submit.prevent="handleSubmit">
      <input type="text" v-model="message">
      <button type="submit">提交</button>
    </form>
  </template>

  <script>
  export default {
    methods: {
      handleSubmit() {
        console.log(this.message)
      }
    }
  }
  </script>
  ```

  上述代码中，我们在表单上使用`.prevent`修饰符来阻止表单的默认提交行为。因此，当你点击提交按钮时，不会触发表单的默认提交行为，而是只会调用`handleSubmit`方法。

3. `.capture`

  `.capture`可以用来将事件绑定在父元素上，并在捕获阶段触发事件。

  ```html
  <template>
    <div @click.capture="handleClick">
      点击我
      <button>子元素</button>
    </div>
  </template>

  <script>
  export default {
    methods: {
      handleClick() {
        console.log('父元素被点击了')
      }
    }
  }
  </script>
  ```

  上述代码中，我们在父元素上使用`.capture`修饰符来绑定一个点击事件，并在捕获阶段触发。因此，当你点击子元素时，先触发父元素的点击事件，再触发子元素的点击事件。

4. `.self`

  `.self`可以用来限制事件只在元素自身触发，而不是在内部元素上触发。

  ```html
  <template>
    <div @click.self="handleClick">
      点击我
      <button>子元素</button>
    </div>
  </template>

  <script>
  export default {
    methods: {
      handleClick() {
        console.log('父元素被点击了')
      }
    }
  }
  </script>
  ```

  上述代码中，我们在父元素上使用`.self`修饰符来限制点击事件只能在元素本身触发，而不会在内部的子元素上触发。因此，当你点击子元素时，不会触发父元素的点击事件，只有在父元素上点击时才会触发。

除了上述修饰符之外，Vue还提供了`.once`用于只触发一次事件、`.passive`用于改善移动端滚动性能等其他事件修饰符。  

## 表单输入绑定 `v-model`

### 指令修饰符

## 生命周期

## 组件

## 模板引用 ref

当你在Vue模板中使用ref属性时，它可以让你获取到DOM元素或组件实例的引用。具体来说，当你在模板中写入类似于"`ref='myRef'`"的标记时，Vue会创建一个指向这个DOM元素或组件实例的引用，并将其存储在组件实例中的$refs对象中。

举个例子，假设有一个Vue组件，它包含一个`<input>`标签和一个按钮，点击按钮后想要获取输入框中的值。可以通过在`<input>`标签上添加ref属性来引用该元素，然后在按钮的点击事件中使用`$refs`来访问该元素：

```html
<template>
  <div>
    <input type="text" ref="myInput">
    <button @click="handleButtonClick">Get Input Value</button>
  </div>
</template>

<script>
export default {
  methods: {
    handleButtonClick() {
      const inputValue = this.$refs.myInput.value;
      console.log(inputValue);
    },
  },
};
</script>
```

在上面的例子中，我们给`<input>`标签添加了一个ref属性，其值为"myInput"。在按钮的点击事件中，我们可以通过`this.$refs.myInput`访问到该元素，并获取其value属性，从而得到输入框中的值。



## Props

## 混入 Mixin

## 插件 plugin

## 自定义事件 `$emit`

## 全局事件总线

## 消息订阅与发布 pubsub-js

## 插槽 `v-slot:xx="yy"`

插槽是一种常见的**组件通信机制**，它可以让子组件在渲染过程中，将父组件中的内容插入到指定位置。

### 匿名插槽

### 具名插槽 `v-slot:xx `

### 作用域插槽v-slot:xx="yy"

作用域插槽是 Vue 中的一种插槽。它是一种特殊的插槽，可以向子组件传递数据，并且在子组件内部进行处理和渲染。

通过作用域插槽，父组件可以像子组件传递数据，子组件则可以自定义渲染规则，从而实现更灵活的 UI 处理方式。作用域插槽使用 `<slot>` 元素来声明，同时需要传递一个参数来定义数据的作用域范围。例如：

在父组件中：

```vue
<template>
  <child-component>
    <template v-slot:user="slotProps">
      <span>{{ slotProps.user.firstName }}</span>
      <span>{{ slotProps.user.lastName }}</span>
    </template>
  </child-component>
</template>
```

在子组件中：

```vue
<template>
  <div>
    <slot name="user" :user="{ firstName: 'John', lastName: 'Doe' }"></slot>
  </div>
</template>
```

在以上代码中，父组件向子组件传递了一个名为 "user" 的作用域插槽，在子组件中通过 `slotProps` 对象来访问父组件传递的数据对象。具体来说，`slotProps` 对象中的属性名就是父组件传递的参数名，属性值则是父组件传递的数据对象。

通过作用域插槽，我们可以将更多的渲染逻辑交给子组件处理，这对于一些需要复杂 UI 处理的组件来说，可以极大地提高代码的可读性和可维护性。

## vuex

## 路由



# Vue3

## vite

`npm create vite@latest`

你还可以通过附加的命令行选项直接指定项目名称和你想要使用的模板。例如，要构建一个 Vite + Vue 项目，运行:

```bash
# npm 6.x

npm create vite@latest my-vue-app --template vue

# npm 7+, extra double-dash is needed:

npm create vite@latest my-vue-app -- --template vue
```

### create-vite

create-vite 是一个快速生成主流框架基础模板的工具。

## 组合式函数 hooks

# 项目实战

 



# JS

## 对象

### 对象基础

1. **对象字面量：**使用花括号 `{}` 可以创建一个新的对象，并在大括号内部指定对象的属性和方法。例如：

   ```javascript
   let person = {
     name: "John",
     age: 30,
     sayHello: function() {
       console.log("Hello, I'm " + this.name);
     }
   };
   ```

   > **在对象字面量中的方法，有什么简写方式吗？**
   >
   > 是的，ES6引入了一种新的对象字面量简写语法，可以更轻松地定义方法。使用这种语法，您可以省略冒号和`function`关键字，并将函数定义放在花括号内。
   >
   > 以下是使用简写语法创建与上一个示例相同的对象的示例：
   >
   > ```javascript
   > let person = {
   >   name: "John",
   >   age: 30,
   >   sayHello() {
   >     console.log("Hello, my name is " + this.name);
   >   }
   > };
   > 
   > person.sayHello(); // 输出"Hello, my name is John"
   > ```
   >
   > 在这个例子中，我们仍然定义了一个名为`sayHello`的方法，但是我们删除了冒号和`function`关键字，并将函数定义直接放在花括号中。这使得代码更加简洁易读，并且更加符合常规的面向对象编程语言的语法。

2. **访问对象的属性和方法：**可以使用点号 `.` 或方括号 `[]` 来访问对象中的属性或方法。例如：

   ```javascript
   console.log(person.name); // 输出 "John"
   console.log(person["age"]); // 输出 30
   person.sayHello(); // 输出 "Hello, I'm John"
   ```

3. **继承和原型链：**JavaScript 中的对象可以通过原型链来实现继承关系。通过向原型对象中添加属性和方法，可以使得所有该对象的实例都具有这些属性和方法。

4. **对象属性和方法的增删改查：**可以通过赋值、delete 操作符、Object.defineProperty() 方法等方式来增加、删除、修改和查看对象的属性和方法。例如：

   ```javascript
   person.age = 40; // 修改 age 属性的值为 40
   delete person.sayHello; // 删除 sayHello 方法
   Object.defineProperty(person, "gender", {value: "Male"}); // 添加 gender 属性，值为 "Male"
   ```

5. **内置对象：**JavaScript 中还提供了一些内置对象，比如 Array、Date、RegExp 等，它们都是特殊的对象。您可以使用 new 关键字来创建这些内置对象的实例。

6. **this 关键字：**在对象中，this 关键字表示当前对象本身。可以在方法内部使用 this 来引用对象本身。例如：

   ```javascript
   let person = {
     name: "John",
     sayHello: function() {
       console.log("Hello, I'm " + this.name);
     }
   };
   ```

上面的代码定义了一个名为 person 的对象，并在其内部定义了一个名为 sayHello 的方法。在 sayHello 方法中使用了 this 关键字来引用 person 对象本身。

总之，在 JavaScript 中，对象是一种非常重要的数据类型，它允许您封装相关的数据和行为，并提供了灵活的方式来组织和管理代码。通过深入理解对象的属性、方法、继承和原型链等特性，您可以更好地掌握 JavaScript 编程语言。

### js 内置对象 分类

JavaScript 中有许多内置对象，可以分为以下几类：

#### 原始值对象（Primitive value）

包括：`undefined`、`null`、`boolean`、`number`、`string`和`symbol`。

#### 包装对象（Wrapper object）

在 JavaScript 中，原始值也可以被包装成相应的对象。包装对象是由 JavaScript 自动创建的，用于对原始值进行操作。例如，对于字符串类型的原始值，我们可以使用 `String` 构造函数创建一个字符串对象，然后调用对象的方法来操作字符串。 

#### 内建对象（Built-in object）

内建对象又可称为标准内置对象，是 ECMAScript 标准提供的对象。包括：

- 基本对象：`Object`、`Function`、`Boolean`、`Symbol` 等。
- 错误对象：`Error`、`TypeError`、`RangeError`、`ReferenceError` 等。
- 数字和日期对象：`Number`、`Math`、`Date` 等。
- 字符串对象：`String`、`RegExp` 等。
- 集合对象：`Array`、`Set`、`Map` 等。
- 其他对象：`JSON`、`Reflect`、`Atomics` 等。

#### 宿主对象（Host Object）

宿主对象指由宿主环境提供的对象，如浏览器环境提供的 `window` 和 `document` 对象等。

### 原生对象 API

#### 1. String 类型的常用方法

 正在为您搜索：js中字符串的常用方法、用表格展示、每一种方法用一条记录展示、字段包括参数和返回值

可以，以下是 JavaScript 字符串对象中常用方法的表格展示：

| 方法名称        | 参数                                                         | 返回值                                                       | 描述                                                         |
| --------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| charAt()        | `index`：必需，表示要返回的字符在字符串中的索引位置（0~length-1）。 | 该位置上的字符。                                             | 返回指定位置处的字符。                                       |
| concat()        | 一个或多个字符串。                                           | 连接所有给定字符串后得到的新字符串。                         | 连接两个或多个字符串，返回拼接后的新字符串。                 |
| indexOf()       | `substring`：必需，表示要查找的子字符串；`start`：可选，表示从哪个索引位置开始查找（默认为 0）。 | 子字符串首次出现的索引位置，如果没有找到，返回 -1。          | 查找子字符串在原始字符串中第一次出现的位置。                 |
| lastIndexOf()   | `substring`：必需，表示要查找的子字符串；`start`：可选，表示从哪个索引位置开始查找（默认为字符串末尾）。 | 子字符串最后一次出现的索引位置，如果没有找到，返回 -1。      | 查找子字符串在原始字符串中最后一次出现的位置。               |
| slice()         | `start`：必需，表示要提取的字符串片段的起始索引位置（包括该位置上的字符）；`end`：可选，表示要提取的字符串片段的结束索引位置（不包括该位置上的字符）。如果省略该参数，将会一直提取到字符串末尾。 | 从原始字符串中提取一段子字符串并返回。                       | 提取原始字符串的一个子字符串。                               |
| split()         | `separator`：必需，表示用于分隔字符串的分隔符；`limit`：可选，表示分裂的次数。 | 包含被分隔后的所有子字符串的数组。每个子字符串都是由分隔符分割出来的，分隔符本身不包括在其中。 | 将一个字符串按照指定的分隔符分割成若干个子字符串，返回这些子字符串组成的数组。 |
| toLowerCase()   | 无参数。                                                     | 全部小写的新字符串。                                         | 返回原始字符串的小写形式。                                   |
| toUpperCase()   | 无参数。                                                     | 全部大写的新字符串。                                         | 返回原始字符串的大写形式。                                   |
| replace()       | `searchValue`：必需，表示要替换的子字符串或正则表达式；`replaceValue`：必需，表示替换为的新字符串或新子字符串。 | 替换后的新字符串。                                           | 返回一个由替换操作后的字符串组成的新字符串。                 |
| trim()          | 无参数。                                                     | 去除字符串两端空格后的新字符串。                             | 去掉字符串两端的空格。                                       |
| substr()        | `start`：必需，表示子字符串的起始索引位置；`length`：可选，表示所提取的子字符串的长度。 | 从指定位置开始截取的子字符串。如果省略第二个参数，则返回从起始位置直到字符串末尾的所有字符。 | 指定从字符串中的某个位置开始提取指定长度的字符。             |
| substring()     | `start`：必需，表示子字符串的起始索引位置；`end`：可选，表示子字符串的结束索引位置（不包括该位置上的字符）。 | 从 start 到 end（不包括 end）之间的所有字符。如果忽略第二个参数，则将提取从 start 到字符串末尾的所有字符。 | 提取字符串中介于两个指定下标之间的字符。                     |
| localeCompare() | `compareString`：必需，表示要比较的字符串。                  | 返回一个数字，表示在字母表中的顺序关系。                     | 比较两个字符串并返回比较结果。                               |
| startsWith()    | `searchString`：必需，表示要查找的子字符串；`position`：可选，表示开始查找的位置。 | 如果指定的子字符串位于原始字符串的起始位置，返回 true；否则返回 false。 | 判断原始字符串是否以指定子字符串开始。                       |
| endsWith()      | `searchString`：必需，表示要查找的子字符串；`length`：可选，表示在原始字符串中要匹配的字符数。 | 如果指定的子字符串位于原始字符串的结束位置，返回 true；否则返回 false。 | 判断原始字符串是否以指定子字符串结束。                       |
| match()         | `regexp`：必需，表示要与字符串匹配的正则表达式。             | 如果在字符串中找到了匹配的内容，则返回存放匹配结果的数组；否则返回 null。 | 从字符串中查找与正则表达式匹配的模式。                       |
| search()        | `regexp`：必需，表示要与字符串匹配的正则表达式。             | 如果找到匹配的内容，返回第一个匹配对应的索引值；否则返回 -1。 | 在字符串中查找指定的模式并返回其索引值。                     |
| repeat()        | `count`：必需，表示将这个字符串重复的次数。                  | 返回由原始字符串重复多次得到的新字符串。                     | 将字符串重复指定的次数后返回新的字符串。                     |

需要说明的是，有些方法需要接收参数，如 `charAt()`、`slice()`、`substr()` 和 substring() 等方法，用于返回字符串的一个子集。还有一些方法则无需参数，如 `toLowerCase()`、`toUpperCase()` 和 `trim()` 等方法，直接对字符串进行相应的操作。

#### 2. Number 类型的常用方法

| 方法名称     | 参数                                                         | 返回值                                                    | 描述                                                 |
| ------------ | ------------------------------------------------------------ | --------------------------------------------------------- | ---------------------------------------------------- |
| toFixed()    | `digits`：必需，表示保存几位小数。如果省略该参数，则将数字转换为整数。 | 转换后的新字符串。                                        | 把数字转换为字符串，结果的小数点后有指定位数的数字。 |
| toString()   | `radix`：可选，表示转换后的进制数。默认值为 10。             | 转换后的新字符串。                                        | 把数字转换为字符串。                                 |
| parseInt()   | `str`：必需，表示要解析成整数的字符串；`radix`：可选，表示解析时要使用的基数(从 2 到 36)，默认值为 10。 | 解析成整数的新数字。                                      | 解析一个字符串并返回一个整数。                       |
| parseFloat() | `str`：必需，表示要解析成浮点数的字符串。                    | 解析成浮点数的新数字。                                    | 解析一个字符串并返回一个浮点数。                     |
| isNaN()      | `value`：必需，表示要检测的值。                              | 布尔值，表示是否为 NaN（是则返回 true，否则返回 false）。 | 判断指定值是否为 NaN。                               |

#### 3. Boolean 类型的常用方法

| 方法名称   | 参数     | 返回值                                                | 描述                                                        |
| ---------- | -------- | ----------------------------------------------------- | ----------------------------------------------------------- |
| toString() | 无参数。 | 字符串，表示布尔值的字符串形式（"true" 或 "false"）。 | 转换为字符串，返回字符串形式的布尔值。（"true" 或 "false"） |

#### 4. Array 类型的常用方法

| 方法名称   | 参数                                                         | 返回值                               | 描述                                               |
| ---------- | ------------------------------------------------------------ | ------------------------------------ | -------------------------------------------------- |
| push()     | `item1, ..., itemX`：可选，表示要插入到数组末尾的一个或多个值。 | 数组的新长度。                       | 可向数组的末尾添加一个或更多元素，并返回新的长度。 |
| pop()      | 无参数。                                                     | 删除的那个元素。                     | 从数组的末尾删除最后一个元素，并返回该元素。       |
| shift()    | 无参数。                                                     | 删除的那个元素。                     | 删除数组中的第一个元素，并返回该元素。             |
| unshift()  | `item1, ..., itemX`：可选，表示要插入到数组开头的一个或多个值。 | 数组的新长度。                       | 向数组的开头添加一个或更多元素，并返回新的长度。   |
| sort()     | `compareFunction`：可选，表示排序时使用的比较函数。如果省略该参数，则按字母升序排序。 | 排序后的数组。                       | 对数组的元素进行排序。                             |
| concat()   | `arr1, ..., arrX`：可选，表示要连接到原始数组的一个或多个数组。 | 连接后的新数组。                     | 将两个或多个数组合并为一个数组，并返回新的数组。   |
| slice()    | `start`：可选，表示起始处的索引值。如果是负数，则从末尾开始计算；`end`：可选，表示结束处的索引值（不包含该索引）如果是负数，则从末尾开始计算。如果省略该参数，则表示从起始位置一直提取到末尾。 | 由提取的新数组组成的新数组。         | 返回数组中的选定元素。                             |
| toString() | 无参数。                                                     | 由数组元素组成、以逗号分隔的字符串。 | 把数组转换为字符串，并返回结果。                   |

#### 5. Object 类型的常用方法

| 方法名称               | 参数                                                         | 返回值                                                       | 描述                                                       |
| ---------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ---------------------------------------------------------- |
| assign()               | `target`：必需，表示目标对象；`sources`：必需，表示源对象，可以有一个或多个。 | 目标对象，与源对象属性相同的值将被覆盖，没有的属性将被添加。 | 用于将所有可枚举属性的值从一个或多个源对象复制到目标对象。 |
| propertyIsEnumerable() | `property`：必需，表示检测的属性名称。                       | 布尔值，指示给定属性是否可枚举。                             | 返回指定的属性是否可以枚举。                               |

#### 6. 日期类型的常用方法

| 方法名称          | 参数                                                         | 返回值                                                       | 描述                     |
| ----------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------ |
| getDate()         | 无参数。                                                     | 1~31 之间的一个数字，表示当前日期是这个月的第几天。          | 返回一个月中的第几天。   |
| getDay()          | 无参数。                                                     | 0~6 之间的一个数字，表示当前日期是星期几（0-周日，1-周一，以此类推）。 | 返回一个星期中的第几天。 |
| getFullYear()     | 无参数。                                                     | 当前完整的年份（如：2023）。                                 | 返回一个完整的年份。     |
| getMonth()        | 无参数。                                                     | 0~11 之间的一个数字，表示当前日期所在月份（0-1月，1-2月，以此类推）。 | 返回一个月份。           |
| getHours()        | 无参数。                                                     | 当前小时数（0~23）。                                         | 返回当前时刻的小时数。   |
| getMinutes()      | 无参数。                                                     | 当前分钟数（0~59）。                                         | 返回当前时刻的分钟数。   |
| getSeconds()      | 无参数。                                                     | 当前秒数（0~59）。                                           | 返回当前时刻的秒数。     |
| getMilliseconds() | 无参数。                                                     | 当前毫秒数（0~999）。                                        | 返回当前时刻的毫秒数。   |
| getTime()         | 无参数。                                                     | 返回从 1970 年 1 月 1 日 00:00:00 UTC 到当前日期的毫秒数。   | 返回 Unix 时间戳。       |
| setDate()         | `day`：必需，表示要设置的日期是本月的第几天（1~31）。        | 返回设置后的日期。                                           | 设置一个月中的某一天。   |
| setFullYear()     | `year`：必需，表示要设置的新的年份。                         | 返回设置后的年份。                                           | 设置一个完整的年份。     |
| setMonth()        | `month`：必需，表示要设置的新的月份（0~11）。                | 返回设置后的月份。                                           | 设置一个月份。           |
| setHours()        | `hour`：必需，表示要设置的新的小时数（0~23）；`min`：可选，表示要设置的分钟数；`sec`：可选，表示要设置的秒数；`ms`：可选，表示要设置的毫秒数。 | 返回设置后的小时数。                                         | 设置一个时刻的小时数。   |
| setMinutes()      | `min`：必需，表示要设置的新的分钟数（0~59）；`sec`：可选，表示要设置的秒数；`ms`：可选，表示要设置的毫秒数。 | 返回设置后的分钟数。                                         | 设置一个时刻的分钟数。   |
| setSeconds()      | `sec`：必需，表示要设置的新的秒数（0~59）；`ms`：可选，表示要设置的毫秒数。 | 返回设置后的秒数。                                           | 设置一个时刻的秒数。     |
| setMilliseconds() | `ms`：必需，表示要设置的新的毫秒数（0~999）。                | 返回设置后的毫秒数。                                         | 设置一个时刻的毫秒数。   |

## 构造函数

在 JavaScript 中，构造函数和对象之间有着密切的关系。**构造函数是一种特殊的函数，用于创建新的对象实例。**每个 JavaScript 对象都是通过一个构造函数来创建的。如果您没有明确指定构造函数，则会使用内置的 Object 构造函数来创建对象。

>  **什么叫我没有为对象指定构造函数呢，你能举个这样的例子嘛？**
>
> 当您使用对象字面量创建一个对象时，实际上没有指定任何构造函数。
>
> 例如：
>
> ```js
> const myObj = {
>   name: 'John',
>   age: 30
> };
> ```
>
> 在这个例子中，我们没有直接使用构造函数来创建 `myObj` 对象。相反，我们使用了对象字面量的语法来创建它。由于没有指定构造函数，JavaScript 将默认使用内置的 Object 构造函数来创建这个对象。
>
> 另外，如果您使用关键字 `new` 和一个构造函数来创建对象，但是没有为该构造函数定义任何属性或方法，则仍然会使用默认的 Object 构造函数来创建对象。例如：
>
> ```js
> function Person() {}
> 
> const john = new Person();
> ```
>
> 在这个例子中，我们定义了一个空的构造函数 `Person`，并使用 `new` 关键字创建了一个新的对象 `john`。由于我们没有为 `Person` 构造函数定义任何属性或方法，因此 JavaScript 仍将默认使用 Object 构造函数来创建 `john` 对象。

通过定义自己的构造函数，您可以创建自己的对象类型，并为这些对象类型添加属性和方法。在构造函数中，可以使用 this 关键字来引用正在创建的对象实例，并将属性和方法添加到该实例上。然后，您可以使用 new 关键字来创建新的对象实例，如下所示：

```javascript
function Person(name, age) {
  this.name = name;
  this.age = age;
}

let person1 = new Person("Alice", 25);
let person2 = new Person("Bob", 30);
```

在上面的代码中，我们定义了一个名为 Person 的构造函数，并在其内部使用 this 关键字来分别定义了两个属性 name 和 age。然后，我们使用 new 关键字创建了两个名为 person1 和 person2 的对象实例，它们都具有相同的属性和方法。

通过使用构造函数，您可以轻松地创建大量具有相似属性和方法的对象。例如，在编写 Web 应用程序时，您可能需要创建多个用户对象，每个对象都包含用户名、密码、电子邮件地址等属性。通过使用构造函数，您可以方便地创建多个用户对象，并且每个对象都具有相同的属性和方法。

综上所述，构造函数是一种用于创建新对象实例的特殊函数，它们是 JavaScript 对象的重要组成部分。通过定义自己的构造函数，您可以创建具有特定属性和方法的对象类型，并使用 new 关键字来创建新的对象实例。

## 原型

在JavaScript中，每个对象都是基于一个原型创建的。原型可以看作是一个模板或蓝图，它定义了对象的共享属性和方法。通过使用原型，您可以实现代码重用，并将方法和属性添加到所有对象上。

在JavaScript中，每个构造函数（除了箭头函数）都有一个`prototype`属性，该属性指向一个对象。这个对象包含了构造函数创建的所有实例对象所共享的属性和方法。当调用一个实例对象的属性或方法时，JavaScript引擎会首先查找该对象本身是否具有该属性或方法，如果没有，则会查找其原型对象是否具有该属性或方法。

下面是一个使用原型对象添加方法的例子：

```javascript
function Person(name) {
  this.name = name;
}

Person.prototype.greet = function() {
  console.log('Hello, my name is ' + this.name);
}

let person1 = new Person('张三');
let person2 = new Person('李四');

person1.greet(); // 输出"Hello, my name is 张三"
person2.greet(); // 输出"Hello, my name is 李四"
```

在Python中，您可以将原型类比为类。类是一种定义对象属性和方法的机制。与JavaScript中的原型类似，Python中的类也可以派生出其他类，并继承它们的属性和方法。在Python中，每个对象都是类的一个实例，它们共享类的属性和方法。

以下是一个使用Python类来创建对象的示例：

```python
class Person:
    def __init__(self, name):
        self.name = name
        
    def greet(self):
        print('Hello, my name is', self.name)
        
person1 = Person('张三')
person2 = Person('李四')

person1.greet() # 输出"Hello, my name is 张三"
person2.greet() # 输出"Hello, my name is 李四"
```

在这个例子中，我们定义了一个名为`Person`的类，并使用它创建了两个不同的实例对象。我们还在类中定义了一个`greet`方法，该方法与JavaScript中的示例类似。当我们调用每个对象的`greet`方法时，它们都会显示正确的名字。



## JavaScript  API 分类

1. DOM API：用于操作网页上的 HTML 元素和其他内容的 API，如 document、Element 等。

2. BOM API：用于操作浏览器窗口和历史记录等浏览器相关功能的 API，如 window、navigator、location 等。

3. 原生对象 API：定义在 JavaScript 内置对象上的 API，如 String、Array、Object 等。

4. AJAX API：用于在页面上进行异步数据交互的 API，如 XMLHttpRequest、fetch 等。

5. Web Storage API：用于在客户端存储数据的 API，如 localStorage、sessionStorage 等。

6. Canvas API：用于绘制图形的 API，如 CanvasRenderingContext2D、WebGLRenderingContext 等。

7. Web Worker API：用于创建后台线程以执行耗时任务的 API，如 Worker 等。

8. WebRTC API：用于实现实时音视频通信的 API，如 MediaStream、RTCPeerConnection 等。

以上只是其中的一部分分类方式，不同的分类方式可能会有不同的具体细节和命名方式。

## ES6 新特性

ES6（也称为ECMAScript2015）是JavaScript的一个重要版本，它在语言层面引入了许多新特性，以下列举其中的一些：

1. Arrow Function 箭头函数
2. Class 类
3. Let 和 Const 块级作用域变量声明
4. 模板字符串
5. 解构赋值
6. Promise 异步编程
7. 模块化支持
8. Map 和 Set 数据结构
9. Rest 和 Spread 运算符
10. 默认参数

这仅是 ES6 新特性的冰山一角，ES6 还引入了其他很多方便开发的特性，如迭代器、for-of 循环、Symbol 数据类型、Proxy 对象、Reflect 对象等等。

###  模板字符串

ES6 引入了模板字符串语法，用反引号（`）来创建一个特殊的字符串，支持多行字符串和插值表达式，替代了传统的字符串拼接方式。以下是模板字符串的示例：

```js
const name = '小明';
const age = 18;
const info = `姓名：${name}，年龄：${age}`;
console.log(info);  // 输出：'姓名：小明，年龄：18'
```

在上述代码中，使用了 `${}` 语法来插入变量值，可以减少字符串拼接的麻烦。除了简单的变量插值，还可以在 `${}` 中运用表达式、函数调用等语法。例如：

```js
const a = 10;
const b = 20;
const c = `a + b = ${a + b}`;
console.log(c);  // 输出：'a + b = 30'

function multiply(x, y) {
  return x * y;
}
const result = `2 * 3 = ${multiply(2, 3)}`;
console.log(result);  // 输出：'2 * 3 = 6'
```

模板字符串还支持多行字符串，只需要直接在反引号中换行即可，不需要使用特殊符号或转义字符。例如：

```js
const message = `
  这是一个
  多行
  字符串。
`;
console.log(message);  // 输出：
/*
  '这是一个
  多行
  字符串。'
*/
```

### 解构赋值

1. 数组解构赋值

可以使用数组解构赋值将一个数组分解为多个变量，每个变量分别接收数组中对应位置的元素。例如：

```
const [a, b, c] = ['苹果', '香蕉', '橙子'];
console.log(a, b, c);  // 输出：'苹果' '香蕉' '橙子'
```

如果想要跳过某些元素，可以使用逗号来占位。例如：

```
const [a, , c] = ['苹果', '香蕉', '橙子'];
console.log(a, c);  // 输出：'苹果' '橙子'
```

还可以使用剩余元素语法 `...` 将数组剩余部分赋值给一个新数组。例如：

```
const [a, b, ...rest] = ['苹果', '香蕉', '橙子', '西瓜'];
console.log(a, b);  // 输出：'苹果' '香蕉'
console.log(rest);  // 输出：['橙子', '西瓜']
```

2. 对象解构赋值

可以使用对象解构赋值将一个对象的属性分解为多个变量，每个变量分别接收对象中对应属性的值。例如：

```
const {name, age} = {name: '张三', age: 18};
console.log(name, age);  // 输出：'张三' 18
```

对象解构赋值也可以使用默认值，当属性不存在时，将使用默认值来初始化变量。例如：

```
const {name = '匿名', age = 0} = {};
console.log(name, age);  // 输出：'匿名' 0
```

如果想要将属性重命名为其他变量名，可以使用别名语法。例如：

```
const {name: fullName} = {name: '张三'};
console.log(fullName);  // 输出：'张三'
```

还可以使用嵌套对象解构赋值，将多层次的对象属性依次解构到对应的变量中。例如：

```
const {name, address: {city}} = {name: '张三', address: {city: '北京', country: '中国'}};
console.log(name, city);  // 输出：'张三' '北京'
```

3. 函数参数解构

在定义函数时，可以使用解构赋值语法作为函数参数，将传入的对象分解为多个变量。例如：

```
function showUserInfo({name, age}) {
  console.log(`姓名：${name}，年龄：${age}`);
}

showUserInfo({name: '张三', age: 18});  // 输出：'姓名：张三，年龄：18'
```

参数解构赋值也可以使用默认值和嵌套对象解构的方式。例如：

```
function showAddress({address: {city = '北京', country}}) {
  console.log(`城市：${city}，国家：${country}`);
}

showAddress({address: {country: '中国'}});  // 输出：'城市：北京，国家：中国'
```

综上所述，ES6 的解构赋值可以用于数组、对象、函数参数等多种场景，可以使代码更加简洁、易读。





# CSS

## 三大特性

### 层叠性

顺序，权重都会影响谁覆盖谁

### 继承性

子元素自动应用父元素样式

背景色不能继承

### 优先级



## 样式选择器

### 标签选择器

标签选择器顾名思义就是根据 HTML 代码中的标签，来设置对应的 CSS 样式属性。常见的标签有 `h1`、`p`、`a`、`img` 等等。

```css
/* 使用标签选择器样式化文本 */
p {
  font-size: 16px;
  line-height: 1.5;
}
```

### 类选择器 (.)

类选择器可以根据元素的类名来设置相应的样式效果，可以用`.`符号来表示。

```css
/* 使用类选择器样式化不同类型的按钮 */
.button {
  display: inline-block;
  padding: 10px 20px;
  font-size: 14px;
  border-radius: 4px;
}

.primary {
  background-color: #007bff;
  color: #fff;
}

.secondary {
  background-color: #6c757d;
  color: #fff;
}
```

### ID 选择器 (#)

ID 选择器可以根据元素的 ID 名称来设置相应的样式效果，可以用 `#` 符号来表示。

```css
/* 使用 ID 选择器样式化页面中的导航栏 */
#nav {
  display: flex;
  justify-content: space-between;
  align-items: center;
  background-color: #008080;
  color: #fff;
  height: 60px;
  padding: 0 20px;
}
```

### 属性选择器 ([])

属性选择器可以根据元素的属性来进行选择。例如，下面的选择器会选中所有有 `href` 属性的链接元素。

```css
/* 使用属性选择器样式化页面中的链接 */
a[href] {
  text-decoration: none;
  color: #007bff;
}
```

### 交集选择器()

选择器之间直接连接，没有任何符号或者空格

### 并集选择器(,)

选择器之间用逗号（，）分隔

### 伪类选择器 (:)

伪类选择器用于选中元素的特定状态，例如鼠标悬停在链接上时的状态（`:hover`），或者某个元素是其父元素中的第一个子元素（`:first-child`）。

```css
/* 使用伪类选择器样式化页面中的链接 */
a:hover {
  text-decoration: underline;
}

li:first-child {
  margin-top: 0;
}
```

基本伪类选择器：
- :link
- :visited
- :hover
- :active
- :focus

结构性伪类选择器：
- :first-child
- :last-child
- :nth-child(n)
- :nth-last-child(n)
- :nth-of-type(n)
- :nth-last-of-type(n)
- :first-of-type
- :last-of-type
- :only-of-type

表单伪类选择器：
- :checked
- :disabled
- :enabled
- :indeterminate
- :optional
- :required
- :valid
- :invalid

状态伪类选择器：
- :target
- :root
- :empty
- :fullscreen

否定伪类选择器：
- :not()

伪元素选择器：
- ::before
- ::after
- ::first-letter
- ::first-line
- ::selection


需要注意的是，随着CSS的不断发展，新的伪类选择器也应运而生。因此，在实际开发中，我们应该根据具体的需求和场景来选择使用相应的伪类选择器，以达到最佳的效果和体验。

### 兄弟选择器 (+ ~)

相邻兄弟选择器用于选取指定元素之后紧跟着的元素。例如，下面的选择器会选中每个 `h2` 元素后面紧跟着的第一个 `p` 元素，并且只有兄弟标签即`p`会应用样式，如果`p`跟`div`不相邻则不应用，且当有两个`p`相邻时，只有下面的会应用。

```css
/* 使用相邻兄弟选择器样式化页面中的标题与段落 */
h2 + p {
  font-size: 14px;
  line-height: 1.5;
  margin-top: 10px;
}
```

### 子元素选择器 (>)

子元素选择器用于选取指定元素的子元素。例如，下面的选择器会选中每个 `.list` 元素下的直接子元素 `li` 元素。

```css
/* 使用子元素选择器样式化页面中的列表 */
.list > li {
  margin-bottom: 10px;
}
```

### 后代元素选择器 (space)

后代元素选择器用于选取指定元素的后代元素。例如，下面的选择器会选中每个 `article` 元素下的所有 `p` 元素。

```css
/* 使用后代元素选择器样式化页面中的文章内容 */
article p {
  font-size: 16px;
  line-height: 1.5;
  margin-bottom: 10px;
}
```

以上是主要的样式选择器，您可以根据具体的样式需求，灵活地使用这些选择器进行 CSS 样式的设计与编写。



## 元素显示模式

在 CSS 中，元素的显示模式（Display mode）是指控制元素如何显示和布局的属性。以下是常见的 CSS 元素显示模式：

1. `block`：将元素显示为块级元素，并且总是在新行上开始。
2. `inline`：将元素显示为行内元素，与其他行内元素在同一行上。
3. `inline-block`：将元素显示为行内块级元素，同时保留块级元素的特性。
4. `none`：元素不会被显示并从文档流中移除，用于隐藏元素。
5. `table`、`inline-table`、`table-row`、`table-cell` 等：用于控制表格相关的属性。
6. `flex`、`inline-flex`：用于实现弹性盒子布局。

通过设置元素的 display 属性，可以改变元素的显示模式，从而实现不同的布局效果。需要注意的是，一些元素的默认显示模式是块级或行内元素，如果想要改变其默认模式，需要通过 CSS 来设置。

- 块级元素

  块级元素（Block-level elements）在 HTML 中具有以下特点：

  1. 默认会占据一行，即前后都有换行符，不与其它元素显示在同一行上。
  2. 可以通过 CSS 的 width 和 height 属性来设置宽度和高度。
  3. 可以设置 margin（外边距） 和 padding（内边距）属性，用于调整元素与周围元素的距离。
  4. 常见的块级元素有 `<div>`、`<p>`、`<h1>`-`<h6>`、`<ul>`、`<ol>`、`<li>`、`<table>`、`<form>` 等。
  5. 块级元素可以包含内联元素和其他块级元素。
  6. 块级元素可以作为其他元素的父元素容纳子元素。

  由于块级元素的默认行为是独占一行，因此常用于构建网页布局和结构。对于需要让多个元素在同一行上显示的情况，可以使用内联元素或改变块级元素的 display 属性为 inline 或 inline-block 来实现。

- 行内元素

  在 HTML 中，行内元素（Inline elements）具有以下特点：

  1. 默认情况下不会以块的形式展现，而是与文本内容一起显示。
  2. 不能通过 width、height 属性来设置元素的宽度和高度，其宽度和高度由内容撑开。
  3. 不能设置 margin-top 和 margin-bottom 属性，只能设置 margin-left 和 margin-right 属性。
  4. 常见的行内元素有 `<a>`、`<span>`、`<strong>`、`<em>`、`<img>`、`<input>` 等。
  5. 行内元素可以嵌套其他行内元素，并且不能直接包含块级元素。

  由于行内元素的默认行为是与文本内容一起显示，因此常用于容纳文本内容，比如链接、强调文本等。对于需要让元素以块的形式展现或设置元素的宽度、高度等属性时，可以使用 CSS 的 display 属性将其转换为块级元素或 inline-block 元素。

- 行内块级元素（Inline-block elements）是一种特殊的元素，它同时拥有行内元素和块级元素的特点。在 HTML 中，行内块级元素具有以下特点：

  1. 默认情况下不会以块的形式展现，而是与文本内容一起显示。
  2. 可以通过 width、height 属性来设置元素的宽度和高度。
  3. 可以设置 margin 和 padding 属性，用于调整元素与周围元素的距离和内部内容的间距。
  4. 常见的行内块级元素有 `<img>`、`<input>` 等。
  5. 行内块级元素可以嵌套其他行内块级元素或行内元素，并且不能直接包含块级元素。

  由于行内块级元素的特殊性质，它们通常被用于实现一些特定的布局效果，比如图片与文字对齐、按钮组件等。当需要让元素以块的形式展现时，可以使用 CSS 的 display 属性将其转换为块级元素。



## 盒子模型







## 模态框案例代码

在HTML中，&times;是一种特殊的编码符号，表示乘号（multiplication sign）。它通常用于创建一个“关闭”（close）图标，因为它看起来像一个叉子或“X”。在这种情况下，它代表着关闭某个窗口、弹出框或其他UI元素的操作。

```html
{% if message %}
<div class="modal" style="display: block;">
  <div class="modal-content">
    <span class="close">&times;</span>
    <p>{{ message }}</p>
  </div>
</div>
{% endif %}

```

- `.close:focus` 是一个 CSS 选择器，表示当用户通过键盘或鼠标将元素聚焦时，将应用在该元素上的样式规则。`:focus` 伪类选择器用于匹配当前获得焦点的元素。在这个例子中，当用户点击关闭按钮（class 为 "close"）时，close 按钮会获得焦点并且将应用 `.close:focus` 定义的样式规则。所以我们可以利用 `:focus` 选择器来实现一些有趣的效果，例如：添加一个特殊的边框、改变背景色、更改文本颜色等等。

- `text-decoration: none;` 是一个 CSS 样式属性，它指定了文本装饰的样式。`none` 值将删除链接的下划线。在这个例子中，`.close` 元素是一个链接或者按钮，如果不设置 `text-decoration: none;`，那么它会显示带有下划线的文本，这不符合关闭按钮的视觉效果，因为我们通常不希望看到有下划线的按钮。

- `cursor: pointer;` 也是一个 CSS 样式属性，它定义了用户鼠标悬停在元素上面时的光标形状。当鼠标悬停在 `.close` 元素上时，光标会变成手型，表示该元素可以被点击。如果不设置 `cursor: pointer;`，则鼠标在上面悬停时，光标可能会是其他类型，如默认的箭头光标，这会给用户带来困惑，他们可能会认为这个元素不能被点击。

```css
/* 模态框背景蒙层样式 */
.modal {
  position: fixed;
  z-index: 9999;
  left: 0;
  top: 0;
  width: 100%;
  height: 100%;
  background-color: rgba(0, 0, 0, 0.5);
}

/* 模态框内容样式 */
.modal-content {
  background-color: #fff;
  border-radius: 10px;
  box-shadow: 0px 2px 8px rgba(0, 0, 0, 0.3);
  margin: 15% auto;
  padding: 20px;
  max-width: 500px;
  text-align: center;
}

/* 关闭按钮样式 */
.close {
  color: #aaa;
  float: right;
  font-size: 28px;
  font-weight: bold;
}

.close:hover,
.close:focus {
  color: black;
  text-decoration: none;
  cursor: pointer;
}

```

```js
// 获取模态框元素
var modal = document.querySelector('.modal');

// 获取关闭按钮元素
var closeBtn = document.querySelector('.close');

// 点击关闭按钮时隐藏模态框
closeBtn.addEventListener('click', function () {
  modal.style.display = 'none';
});

// 在页面加载完成后显示模态框
window.onload = function () {
  modal.style.display = 'block';
};

```





## 文字垂直居中

要使文本垂直居中，您可以使用以下方法：

1. 使用 line-height 属性：设置行高等于元素的高度减去字体大小，行高和元素高度相等时，文本就会垂直居中。

```css
.container {
  height: 100px;
  line-height: 100px; /* 行高等于元素高度 */
}
```

1. 使用 display 和 vertical-align 属性：将元素设置为表格单元格（table-cell）或内联块级元素（inline-block），并将其与父元素的 vertical-align 属性设置为 middle。

```css
.container {
  display: table-cell; /* 设置为表格单元格 */
  vertical-align: middle; /* 垂直居中对齐 */
}
```

1. 使用 flexbox 布局：将父元素设置为弹性容器（display: flex），并使用 align-items 属性将子元素垂直居中对齐。

```css
.container {
  display: flex; /* 设置为弹性容器 */
  align-items: center; /* 垂直居中对齐子元素 */
}
```

1. 使用 grid 布局：将父元素设置为网格容器（display: grid），并使用 align-items 属性将子元素垂直居中对齐。

```css
.container {
  display: grid; /* 设置为网格容器 */
  align-items: center; /* 垂直居中对齐子元素 */
}
```

这些方法可以使文本垂直居中，具体使用哪种方法取决于您的需求和实际情况。
