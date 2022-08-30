# 一：

下载 [HorseJs](https://gitee.com/horsejs/horsejs/releases) 的二进制文件（扩展名为 7z 的压缩包）解压后，启动压缩包内的 HorseJs.exe，进入 Demo 界面可以看到随 SDK 附带的各种 API 的示例；

<div align=center>
<img src="Doc/Demo.png" />
</div>

# 二：

在你的前端工程下执行如下指令安装 HorseJs 的 npm 包

```cmd
npm install horsejs.org
```

之后你就可以使用如下方式调用 HorseJs 为你提供的 API 了

```js
import { horse } from "horsejs.org";
await horse.window.openDevTool();
```

> HorseJs 的 npm 包并非原生模块，无需本地编译
>
> 你可以自由的使用 Vue、React、Angular 或者其他的现代前端框架构建你的前端项目

# 三：

修改第一步中下载的文件：HorseJs\app\horse.config.json

使其 startPath 配置项指向你的调试地址，比如：

```url
"startPath": "http://localhost:3000/"
```

再次启动 HorseJs.exe，观察你的调试页面在 HorseJs 下的表现

> HorseJs 内置 Chromium 浏览器核心，支持热更新，你可以把它当做一个浏览器

# 四：

开发完成后，把你的前端工程构建产物 ，放置到 HorseJs\app\ 目录下，（该目录下原有的文件，除 horse.config.json 外均应删除），并再次修改 horse.config.json 的 startPath 配置项，使其指向你的起始页面，比如：

```url
"startPath": "app/index.html"
```

# 五：

你可以使用 [Resource Hacker](http://angusj.com/resourcehacker/) 之类的工具修改 HorseJs.exe 的图标或属性信息；

你可以使用 [NSIS](https://nsis.sourceforge.io/) 或 [InnoSetup](https://jrsoftware.org/isinfo.php) 之类的工具把 HorseJs 目录下的内容制作成一个安装文件，分发给你的用户；

> 以后我会提供相应的工具链方便开发者使用它们
