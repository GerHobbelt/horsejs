# 快速入门

## 环境搭建

1.  下载 HorseJs 的二进制文件并解压到目录 yourAppName 中，这个目录的名字你可以随便取
2.  在 yourAppName 的目录下新建 app 子目录，并把你的静态文件（HTML,JS 与 CSS）放置到该目录下，而且 app 目录下必须包含一个名为 index.html 的文件，应用的第一个窗口将加载这个文件。
3.  启动 HorseJs.exe 你将会看到你的第一个应用；

## 应用配置

你可以在 yourAppName 目录下创建一个 horse.json 的文件，

这是整个应用程序的配置文件，

在“环境搭建”环节启动的应用是一个无标题栏的窗口，

如果你想让窗口具备系统提供的标题栏，那么你可以在这个文件中提供如下配置。更详细的配置说明，请参见：[配置文件](Config.md)

```json
{
  "frameless": false
}
```

_你可以通过在你的静态页面中使用-webkit-app-region 样式来实现自己的标题栏，详见：[可拖拽区域](AppRegion.md)_

## 全局对象

在每个窗口创建之初我们就为开发者准备了一个全局对象：horse

开发者可以使用这个对象完成一系列的操作，比如：最大化当前窗口

```javascript
horse.window.maximize();
```

更详细的配置说明，请参见：[全局对象](Horse.md)

## 应用分发

目前来看，你可以使用如下方式分发你的产品：

你可以使用 [Resource Hacker](http://angusj.com/resourcehacker/) 之类的工具修改 HorseJs.exe 的图标或属性信息；

你可以使用 [NSIS](https://nsis.sourceforge.io/) 或 [InnoSetup](https://jrsoftware.org/isinfo.php) 之类的工具把 yourAppName 目录下的内容制作成一个安装文件，分发给你的用户；

将来我会提供必要的工具，来帮你完成这些工作。
