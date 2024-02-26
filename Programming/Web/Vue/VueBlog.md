需要安装的依赖

```json	
{
  "name": "vue-blog",
  "version": "0.0.0",
  "private": true,
  "scripts": {
    "dev": "vite --open",
    "build": "vite build",
    "preview": "vite preview"
  },
  "dependencies": {
    "@ant-design/icons-vue": "^6.1.0",
    "ant-design-vue": "^3.2.20",
    "bulma": "^0.9.4",
    "pinia": "^2.0.36",
    "vue": "^3.3.2",
    "vue-router": "^4.2.0"
  },
  "devDependencies": {
    "@vitejs/plugin-vue": "^4.2.3",
    "sass": "^1.62.1",
    "unplugin-vue-components": "^0.24.1",
    "vite": "^4.3.5"
  }
}
```



配置插件

```js
//  vite.config.js

import { fileURLToPath, URL } from 'node:url'

import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import Components from 'unplugin-vue-components/vite';
import { AntDesignVueResolver } from 'unplugin-vue-components/resolvers';

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [
    vue(),
      // 在这里配置插件
    Components({
      resolvers: [AntDesignVueResolver()],
    }),
  ],
  resolve: {
    alias: {
      '@': fileURLToPath(new URL('./src', import.meta.url))
    }
  }
})

```



配置全局变量

```js
// base.js

import { message, notification } from 'ant-design-vue';
//vite只能用 ant-design-vue/es 而非 ant-design-vue/lib
import 'ant-design-vue/es/message/style/css';
import 'ant-design-vue/es/notification/style/css';

export default {
    install(app) {
        app.config.globalProperties.$message = message
        app.config.globalProperties.$notification = notification
    }
}
```

```js	
// main.js

import { createApp } from 'vue'
import { createPinia } from 'pinia'

import App from './App.vue'
import router from './router'
// 引入base.js
import base from './base'

const app = createApp(App)

app.use(createPinia())
app.use(router)
app.use(base)
app.mount('#app')
```



使用ant-design-vue组件库

```vue
<!-- @/components/Test.vue -->

<script setup>
import { StepBackwardOutlined } from '@ant-design/icons-vue'
import { getCurrentInstance } from 'vue';
const { proxy } = getCurrentInstance()
const info = () => {
	proxy.$message.info('This is a normal message');
};

const openNotification = () => {
	proxy.$notification.open({
		message: 'Notification Title',
		description: 'This is the content of the notification. This is the content of the notification. This is the content of the notification.',
		onClick: () => {
			console.log('Notification Clicked!');
		},
	})
}
</script>

<template>
	<step-backward-outlined />
	<a-button type="primary" @click="info">Display normal message</a-button>
	<a-button type="primary" @click="openNotification">Open the notification box</a-button>
</template>

<style scoped></style>
```

