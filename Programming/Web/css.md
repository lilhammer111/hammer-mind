## 小问题汇总

### 页面/盒子水平居中

盒子模型--margin

### 去掉li中的小圆点

`list-style: none;`

### 圆角边框

`border-radius: 5px;`

### 盒子阴影

`box-shadow: 影子水平位置 影子垂直位置 模糊距离 影子尺寸 颜色 内外阴影;`

`box-shadow: inset hoff voff blur #000;`

### 文字阴影

` text-shadow: hoff voff blur #000;`

## 暂不分类

### 文本居中

```css
.nav a {
    display: inline-block;
    width: 120px;
    height: 58px;
    background-color: pink;
    /* 文本水平居中 */
    text-align: center;
    /* 文本垂直居中 */
    line-height: 58px;
}
```



## 开发准备

fiel://绝对路径，在网页打开.html文件

### 插件

#### auto rename tag

前后标签一起变化

#### open in browser

#### Live Server

实时预览

#### vscode-icons

#### easy less

### 快捷键

#### crtl + D

选中一个后，按crtl+d快速选中相同的

#### crtl + D + 上下箭头

上下移动行

#### crtl + alt + 上下箭头

快速选中多个

#### crtl + h

全局替换

#### shift + alt 

选中块

#### shift + alt + a

多行注释

### Emmet语法

#### 快捷生成html标签

div*3

ul>li

div+p

.demo #two

a{}

$自增

### CSS书写顺序

1. 布局定位属性: display /position /float /overflow
2. 自身属性: width height margin padding border background
3. 文本属性: color font text-align
4. 其他属性（css3）: content cursor box-shadow 



## 选择器

### 基础选择器

基础选择器分为通配选择器，元素选择器，类选择器，ID选择器，属性选择器

#### 属性选择器

### 并集选择器（分组选择器）

`div, p {}`

### 复合选择器

#### 后代选择器

`ol li {}`

#### 子代选择器

`div > p {}`

#### 兄弟选择器

`div + p {}`

+只选中后面第一个兄弟不选中自己，如果p不是div后的第一个元素则无法选中

`div ~ p {}`

~选中后面所有的p元素

### 伪类选择器

#### link伪类选择器

##### 去掉下划线

去掉链接的下划线：`text-decoration: none;`

##### a:link

未被访问过的链接

##### a:visited

已被访问过

##### a:hover

鼠标悬浮

##### a:active

鼠标按下



#### focus伪类选择器

`input:focus {}`



#### 结构伪类选择器

`:first-child`

`:first-of-type`

`:ntb



### 伪元素选择器



## 背景

### 图片

`background-image: url(your_url)`

### 平铺

`background-repeat: no-repeat`

### 位置

`background-position:x y`

只写一个值，另一个默认居中

可以是方位名词： center top left right bottom

可以是精确坐标： x , y 

也可以方位名词和精确坐标混合

例如,20px 50px

### 滚动

`background-attachment: scroll| fixed;`

### 复合写法

`background: 颜色 图片 平铺 滚动 位置

### 背景色半透明

`background: rgba(0,0,0,0.3);`

0.3对应的前面的a即alpha透明度

0.3可以直接写成.3



## CSS三大特性

### 层叠性（覆盖性）

就近原则

### 继承性

可继承的：

text- font- line- color

行高的继承

`font: 12px/1.5 ;`

1.5是行高



#### 设置继承祖先样式：

`color: inherit;`

### 优先级

解决不同标签的属性覆盖问题

如图：

| 选择器            | 选择器权重 |
| ----------------- | ---------- |
| 继承或*           | 0,0,0,0    |
| 元素选择器        | 0.0.0.1    |
| （伪）类选择器    | 0.0.1.0    |
| ID选择器          | 0.1.0.0    |
| 行内样式 style='' | 1.0.0.0    |
| !important 重要的 | 无穷大     |

!important：

`color:pink!important;`

#### 权重叠加

如果是复合选择器，则权重叠加

div ul li 的权重就是0 0 0 3

## 盒子模型

### 其他问题

> 如何清除浏览器默认内外边距？

```css
* {
	margin: 0;
	padding: 0;
}
```

> tips: 
>
> 背景颜色会延伸到内边距，甚至边框上

> tips:
>
> box-sizing属性用来指定可见框的计算方式：
>
> content-box，默认值
>
> 

### 组成

border padding margin content

### border 边框

#### 基本属性

属性：border-width,border-style,border-color

复合写法： `border: 1px solid red`

或者border-top, border-left 

#### 合并相邻边框

`border-collapse: collapse;` 

### padding 内边距

#### 复合写法

`padding: 5px;`上下左右

`padding: 5px 10px;`上下，左右

`padding: 5px 10px 20px;`上，左右，下

`padding: 5px 10px 20px 30px;`上，右，下，左

#### 特殊情况

> 如果子元素没有指定width，那padding就不会撑开父级盒子

### margin 外边距

#### 复合写法

同padding

#### 典型应用

> 如何让块级盒子水平居中？

1. 盒子指定宽度
2. 盒子左右外边距设为auto

> 行内元素和行内块元素如何居中？

行内元素和行内块元素可以看作是text文本，只需为父元素设置`text-align: center;`

#### 相邻合并问题

#### 嵌套块塌陷问题

解决方案

1. 为父元素定义上边框
2. 为副元素定义上内边距
3. 为副元素添加`overflow: hidden;`



## 浮动 float

### 清除浮动

#### 第一种

额外标签法

```html
<!-- 必须是块及元素 -->
<div style="clear: both;"></div>
```

#### 第二种

给父元素添加`overflow: hidden;`

#### 第三种

:after 伪元素法

```html
<style>
	.clearifx:after { 
		content: '';
		display: block;
		height: 0;
		clear: both;
		visibility: hidden;
	}

	.clearifx {
        /* ie6,7兼容 */
		*zoom: 1;
	}
</style>
```

#### 第四种

双伪元素

```html
<style>
	.clearfix:before, .clearfix:after {
		content: '';
		display: table;
	}
	.clearfix:after {
		clear: both;
	}
	.clearfix {
		*zoom: 1;
	}
</style>
```



## 定位 position

定位分为绝对定位，相对定位，固定定位，粘性定位

### 绝对定位



## 弹性盒子

块弹性盒子`display: flex;`，值可以是inline-flex表示行内弹性盒子

### 轴

通过`flex-direction`设置轴的方向，row表横轴，column表竖轴，而row-reverse表反转，示例：`flex-direction: row;`。

### 换行

`flex-wrap`可选值：

wrap，自动换行

nowrap，不换行，则溢出

wrap-reverse，从下向上换行

### 轴和换行的简写

`flex-flow: row wrap;`

### 主轴对齐

`justify-content`属性设置元素在主轴上的对齐方式，可选值：

start，默认值，靠左排

end，靠右排

center，居中

space-between，把剩余空间分配到元素之间

space-around，把剩余空间向元素的左右都分配

space-evenly，把剩余空间分配到元素周围，将元素包裹

### 辅轴对齐

 `align-items`设置元素在侧轴的对齐，可选值：

normal，默认值

stretch，拉升

center，居中

`align-content`设置剩余空间在侧轴上的分配，可选值同justify-content

### 伸缩

`flex: grow shrink basis;`可选值

initial：0 1 auto，此为默认值

auto: 1 1 auto

none: 0 0 auto

### 顺序

`order`属性设置元素的顺序
