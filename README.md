# HorseJs

#### 介绍

使用 HTML/JS/CSS 创建更快速、更稳定的桌面应用

#### 说明

HorseJs 是基于 cef 开发的，没有内置 Node.js，它直接使用 C++提供了类似 Electron 或 NW.js 的能力，比如使用 JavaScript 访问文件（或目录）、打开对话框、访问剪切板、创建托盘图标等。

由于没有 Node.js，所以 HorseJs 运行速度更快，Electron 创建一个新的 BrowserWindow 是非常低效的，HorseJs 就没有这个问题，同样的，少了了很多 Node.js 的干扰，HorseJs 应用也会变得更稳定。

HorseJs 可以直接加载 webpack 或 Rollup 构建的任何前端项目，开发者可以在这类项目中使用任何 npm 包，因为构建工具会把你的依赖包构建到你的最终产物中，但 HorseJs 并不支持在生产环境中加载 Node.js 的原生组件。

目前此项目尚处于实验验证阶段，将来我会逐步为其添加各项功能

#### 起步

1.  xxxx
2.  xxxx
3.  xxxx

#### 使用说明

1.  xxxx
2.  xxxx
3.  xxxx

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request

#### 特技

1.  使用 Readme_XXX.md 来支持不同的语言，例如 Readme_en.md, Readme_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
