配置文件相对于可执行文件(HorseJs.exe)的位置为：app/horse.config.json

但配置文件可有可无，如果开发者没有为应用提供配置文件的话，那么应用会使用 HorseJs 框架提供的默认配置

如下是全量的配置示例，示例中所有配置项的值即为默认值，也就是说，如果开发者没有设置此项配置，程序将按该默认值所代表的意义执行

配置文件中不能有任何注释

```json
{
  "appName": "HorseJs",
  "firstWindow": {
    "autoShow": true,
    "frame": false,
    "startPath": "app/index.html",
    "sizeConfig": {
      "miniSize": {
        "width": 400,
        "height": 300
      },
      "maxSize": {
        "width": -1,
        "height": -1
      },
      "startSize": {
        "width": 800,
        "height": 600
      }
    }
  },
  "version": "0.0.1"
}
```

# appName

应用程序名称

在应用的执行过程中，会使用这个名称来设置一些内容，比如 alert 弹窗的标题、默认数据库路径的目录等

# firstWindow

应用首个窗口的配置项

## startPath

应用第一个窗口加载的页面地址，这个地址可以是一个相对路径，也可以是一个 http 地址

如果把它设置为相对路径的话，那么它是相对于可执行文件(HorseJs.exe)的路径，建议与 horse.config.json 目录相同

如果把它设置为 http 地址的话，那么地址中的 http 必须为小写，其他字符没有限制。

## autoShow

是否启动即马上显示第一个窗口，设置成 false 后续开发者自己调用 horse.window.show();来显示窗口

## frame

是否为有边框窗口，设置成 false 后，窗口不具备标题栏

## sizeConfig

第一个窗口的尺寸配置

### miniSize

第一个窗口的最小尺寸，width 宽度，height 高度

### maxSize

第一个窗口的最大尺寸，width 宽度，height 高度

### startSize

第一个窗口的默认尺寸，width 宽度，height 高度

# version

当前应用程序的版本号
