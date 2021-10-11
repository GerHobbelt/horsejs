配置文件的位置为：app/horse.config.json

但配置文件可有可无，如果开发者没有为应用提供配置文件的话，那么应用会使用 HorseJs 框架提供的默认配置

如下是全量的配置示例，示例中所有配置项的值即为默认值，也就是说，如果你没有设置此项配置，程序将按该默认值所代表的意义执行

配置文件中不能有任何注释

```json
{
  "appName": "HorseJs",
  "startPath": "app/index.html",
  "autoShowFirstWindow": false,
  "version": "0.0.1",
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
}
```

# appName

应用程序名称

# startPath

第一个窗口的启动路径，必须是相对于可执行文件的子路径

# autoShowFirstWindow

是否启动即马上显示第一个窗口，设置成 false 后续开发者自己调用 horse.window.show();来显示窗口

# version

当前应用程序的版本号

# sizeConfig

第一个窗口的尺寸配置

## miniSize

第一个窗口的最小尺寸，width 宽度，height 高度

## maxSize

第一个窗口的最大尺寸，width 宽度，height 高度

## startSize

第一个窗口的默认尺寸，width 宽度，height 高度
