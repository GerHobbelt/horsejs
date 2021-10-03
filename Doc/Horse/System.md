# 方法

## 开机自启动

setOrRemove 值为 "set" 时，为设置开机自启动，值为 "remove" 时，为取消开机自启动。

目前该方法仅支持 Windows 系统

```js
horse.system.setAutoStart({
  setOrRemove: "remove",
});
```
