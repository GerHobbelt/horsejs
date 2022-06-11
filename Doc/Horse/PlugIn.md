HorseJs 基于 wxWidgets 内置的 wxDynamicLibrary 类提供原生插件能力
开发者可以参考如下文档开发自己的原生插件
[WxDynamicLibrary](https://wiki.wxwidgets.org/WxDynamicLibrary)

考虑到大多数应用都会使用本地数据库，所以 HorseJs 的二进制文件中默认附带了 [Sqlite 数据库插件](https://gitee.com/horsejs/horse-js-sqlite)，这个插件在不同系统下对应的动态链接库文件名如下所示：

- HorseSqlite.dll（Windows 操作系统）
- HorseSqlite.so（Mac 操作系统）
- HorseSqlite.dylib（Linux 操作系统）

如果你的应用不会使用本地数据库，那么你可以直接删掉这个动态链接库文件。
