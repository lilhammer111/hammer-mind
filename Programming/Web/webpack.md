## webpack简介

模块打包器（构建工具）



### chunk

### bundle

  

### 常用命令

`webpack --config webpack.config.js`:使用指定的配置文件进行编译。

`webpack --mode production`:设置 Webpack 的模式为生产模式。

`webpack --watch`:开启实时监视文件变化并自动重新编译。

`webpack-cli.run`:在终端中运行 Webpack,并输出编译结果。

`webpack-dev-server`:启动本地开发服务器，用于开发和调试。

### 配置文件

```js
# webpack.config.js

const {resolve} = require('path')
// 引用插件
const htmlWebpackPlugin = require('html-webpack-plugin')

module.exports = {
    // 1.入口文件
    entry: './src/index.js',
    
    // 2.输出位置，默认/dist/main.js
    output: {
    	filename:'build.js',
    	# __dirname根目录名，build为目录名
    	path: resolve(__dirname, 'build')
	}, 
        
    // 3.loader 处理非js资源
    module: {
        rules: [{
            test: /\.css$/,
            {use: ['style-loader', 'css-loader']},
            // {use: [MiniCssExtractPlugin.loader, 'css-loader']}
            // {loader: 'style-loader'} 
        }]       
    }
	// 4.plugin
    plugins:[
        new HtmlWebpackPlugin({
         	template: './src/index.html',
            filename: 'demo.html',
            chunks: ['index', 'vendor']
            minify: {
                // 移除空格
                collapseWhitespace: true,
                // 移除注释
                removeComments: true                
            }
        }),
        new MiniCssExtractPlugin({
            filename: 'demo.css'
        })
    ]
    // 5.mode 生产模式 production 开发模式 development
    mode: 'production', 
    
}
```

### 插件

打包html的插件

html-webpack-plugin

打包css的插件

mini-css-extract-plugin -D





