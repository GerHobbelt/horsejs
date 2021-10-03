# 方法

## 开机自启动

setOrRemove 值为 "set" 时，为设置开机自启动，值为 "remove" 时，为取消开机自启动。

目前该方法仅支持 Windows 系统

```js
await horse.system.setAutoStart({
  setOrRemove: "set",
});
```

## 设置应用启动协议

setOrRemove 值为 "set" 时，为设置开机自启动，值为 "remove" 时，为取消开机自启动。

protocolName 值为协议的名称，假设值为"horse"，则完成此操作后，我们的应用可以识别用户系统内 horse://协议

目前该方法仅支持 Windows 系统

```js
await horse.system.protocolClient({
  protocolName: "horse",
  setOrRemove: "set",
});
```
