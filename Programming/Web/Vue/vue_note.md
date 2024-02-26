# 基础

## 安装准备

```bash
npm init vue@latest
```

安装时，名字一定不要含有大写

```bash
demonwang@demonlinux:~/DemonProjects/vue_test$ npm init vue@latest
Need to install the following packages:
  create-vue@3.6.3
Ok to proceed? (y) y

Vue.js - The Progressive JavaScript Framework

? Project name: › vue-test
```

运行项目

```bash
Done. Now run:

  cd vuetest-project
  npm install
  npm run dev
```

### 自动打开网页

想要浏览器自动打开网页，可以在`package.json`配置文件中添加`--open`

```json
{
  "name": "vue-test-project",
  "version": "0.0.0",
  "private": true,
  "scripts": {
      // 在这里添加--open
    "dev": "vite --open",
    "build": "vite build",
    "preview": "vite preview"
  },
  "dependencies": {
    "vue": "^3.2.47"
  },
  "devDependencies": {
    "@vitejs/plugin-vue": "^4.2.1",
    "vite": "^4.3.4"
  }
}
```



## 事件处理

事件处理函数可以直接接收到事件参数对象event



## 响应式

### ref

想要让ref在js中也自动解包（也即，不写.value），可以在vite.config.js文件中添加`reactivityTransform: true`配置：

```js
import { fileURLToPath, URL } from 'node:url'
import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
export default defineConfig({
  plugins: [vue({
    // 这个是要添加的配置
    reactivityTransform: true
  })],
  resolve: {
    alias: {
      '@': fileURLToPath(new URL('./src', import.meta.url))
    }
  }
})
```

添加完之后，直接使用$ref:

```vue
<script setup>
const father = $ref('demon')
</script>
```





## 列表渲染

### template容器

当我想遍历多个标签（即一个标签组）时，可以借用template容器进行遍历

```vue
<script setup>
import { ref } from 'vue';
const items = ref([{ msg: '奔驰' }, { msg: '宝马' }, { msg: '马自达' }])
</script>

<template>
  <ul>
    <!-- 因为v-for要遍历的是两个标签，所以需要使用一个template容器来装这两个标签 -->
    <template v-for="item in items">
      <li>{{ item.msg }}</li>
      <li class="divider"></li>
    </template>
  </ul>
</template>
```



### 解构

当我遍历对象数组时，我可以直接解构出对象的多个属性

```vue
<script setup>
import { ref } from 'vue';

const objs = ref([
  {
    name: 'Demon',
    age: 26,
    gender: 'male'
  },
  {
    name: 'Jojo',
    age: 30,
    gender: 'female'
  },
  {
    name: 'Hammer',
    age: 1,
    gender: 'male'
  }
])
</script>

<template>
  <ul>
    <li v-for="{ name, age, gender } in objs">{{ name }}--{{ age }}--{{ gender }}</li>
  </ul>
</template>
```

结果：

![image-20230523184627126](/home/demonwang/.config/Typora/typora-user-images/image-20230523184627126.png)







## 组件

### 动态组件

用于切换显示两个不同的组件，利用is属性，值可以是div,p等标签，也可以是A， B等组件

```vue	
<script setup>
import { ref } from 'vue';
import A from './components/A.vue';
import B from './components/B.vue';
const isShow = ref(true)
</script>

<template>
  <button @click="isShow = !isShow">切换</button>
  <component :is="isShow ? A : B">我是component</component>
</template>
```





# 进阶

## 插槽

插槽的性质：

1. 通过使用插槽，组件可以用在不同的地方渲染各异的内容，但同时还保证都具有**相同的样式**。
2. 插槽内容可以访问到父组件的数据。想要访问到父组件数据，则可以像props那样，在插槽出口上传递数据（也即作用域插槽，这里实际是由下向上的传props），这里是实现了**兄弟组件间的通信**。
3. 在外部没有提供任何内容的情况下，可以为插槽指定默认内容。
4. 使用具名插槽，可以实现多对多的插入内容



性质一：

```vue	
<script setup>
import MyButton from './components/MyButton.vue'
import A from './components/A.vue';
</script>

<template>
  <h1>APP组件</h1>
  <!-- 插槽入口，可以是文本，也可以是组件 -->
  <MyButton>这是App自定义的文字</MyButton>
  <MyButton><A></A></MyButton>
</template>
```

![image-20230524012558881](/home/demonwang/.config/Typora/typora-user-images/image-20230524012558881.png)

性质二：





## 透传

写在组件上标签上的属性（除props emit外）会传递给组件的根元素标签上，多根组件不透传

```vue
<!-- src/component/Child.vue -->
<template>
    <div>
        <div>我是child组件</div>
    </div>
    <!-- <div>我也是child组件</div> -->
</template>
```

```vue
<!-- src/App.vue -->
<script setup>
import Child from './components/Child.vue';
</script>

<template>
	<Child class="box2"></Child>
</template>
```

使用`$attrs`访问透传的属性，因此可以在多根节点中手动绑定透传属性

```vue
<template>
    <div>
        <div>我是child组件</div>
    </div>
    <div v-bind="$attrs">我也是child组件</div>
</template>
```

在js中访问透传属性：

```vue
<script setup>
import { useAttrs } from 'vue'

const attrs = useAttrs()
</script>
```

禁用透传需要额外写一个`<script></script>`

```vue
<script>
// 使用普通的 <script> 来声明选项
export default {
  inheritAttrs: false
}
</script>

<script setup>
// ...setup 部分逻辑
</script>
```





## axios

将axios设置为全局变量，并设置baseURL和跨域

```js
import { createApp } from 'vue'
import App from './App.vue'
import axios from 'axios'
// 设置baseURL
axios.defaults.baseURL = 'https://aa43ac5c-d862-4ecc-9ff3-58ba2ad931a5.mock.pstmn.io'
// 设置跨域
axios.defaults.crossDomain = true
const app = createApp(App)
// 设置为全局属性
app.config.globalProperties.$axios = axios


app.mount('#app')
```

调用$axios

```vue
<template>
    <button @click="sendGet">查看教程</button>
</template>

<script>
import { getCurrentInstance } from 'vue';
export default {
    setup() {
        const { proxy } = getCurrentInstance()
        async function sendGet() {
            const res = await proxy.$axios.get('/tutorial')
            console.log(res.data);
        }

        return {
            sendGet
        }
    }
}
</script>

<style scoped></style>
```

