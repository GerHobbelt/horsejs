# 基础信息

## 属性

- 当前框架的版本号

```javascript
horse.info.horseVersion;
```

- 当前应用的版本号

```javascript
horse.info.appVersion;
```

- 当前系统名

```javascript
horse.info.osName;
```

- 当前系统架构

```javascript
horse.info.osArch;
```

## 方法

### 获取系统路径

- home 用户的 home 文件夹（主目录）
- appData 每个用户的应用程序数据目录，默认情况下指向：
- %APPDATA% Windows 中
- $XDG_CONFIG_HOME or ~/.config Linux 中
- ~/Library/Application Support macOS 中
- userData 储存你应用程序设置文件的文件夹，默认是 appData 文件夹附加应用的名称
- 缓存
- temp 临时文件夹
- exe 当前的可执行文件
- module The libchromiumcontent 库
- desktop 当前用户的桌面文件夹
- documents 用户文档目录的路径
- downloads 用户下载目录的路径
- music 用户音乐目录的路径
- pictures 用户图片目录的路径
- videos 用户视频目录的路径
- recent 用户最近文件的目录 (仅限 Windows)。
- logs 应用程序的日志文件夹
- crashDumps 崩溃转储文件存储的目录。

```js
horse.info.getPath({ name: "" });
```
