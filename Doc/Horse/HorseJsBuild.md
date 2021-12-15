# HorseJs 源码构建指南（此文档尚未完成）

此文档不是提供给普通开发者的，而是提供给那些希望为 HorseJs 贡献代码的专业人员的

首先在[wxWidgets 官网下载页面](https://www.wxwidgets.org/downloads/)下载 wxWidgets 的源码安装包（Windows Installer）

下载安装完成后，在安装目录\build\msw 子目录下，找到适合你的工程文件，VS2019 对应的是 wx_vc16.sln

打开工程，把工程下每个子项目的 Release 运行库改为多线程（/MT），Debug 运行库改为（/MTd）

<div align=center>
<img src="HorseJsBuild/mt.png" />
</div>

为每个子项目增加预处理器定义

```
_ITERATOR_DEBUG_LEVEL=0
```

以 Release 的方式重新生成整个解决方案，执行完成后，把整个 wxWidgets 源码拷贝至 HorseJs 跟目录下的 wxWidgetsRelease 文件夹内

删除 wxWidgets 源码目录下 lib\vc_x64_lib 子目录下的所有内容，然后以 Debug 的方式再次重新生成整个解决方案，执行完成后，把整个 wxWidgets 源码拷贝至 HorseJs 跟目录下的 wxWidgetsDebug 文件夹内

以下内容 HorseJs 已经配置好了，不需要自行配置：

```
C++附加包含目录:
$(SolutionDir)wxWidgetsDebug\include;$(SolutionDir)wxWidgetsDebug\include\msvc
```

```
连接器附加库目录
$(SolutionDir)wxWidgetsDebug\lib\vc_x64_lib
```
