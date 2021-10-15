# 开机自启动

- setOrRemove 值为 "set" 时，为设置开机自启动，值为 "remove" 时，为取消开机自启动。

目前该方法仅支持 Windows 系统

```js
await horse.system.setAutoStart({
  setOrRemove: "set",
});
```

# 设置应用启动协议

- setOrRemove 值为 "set" 时，为设置开机自启动，值为 "remove" 时，为取消开机自启动。

- protocolName 值为协议的名称，假设值为"horse"，则完成此操作后，我们的应用可以识别用户系统内 horse://协议

目前该方法仅支持 Windows 系统

```js
await horse.system.protocolClient({
  protocolName: "horse",
  setOrRemove: "set",
});
```

# 发送系统消息

- title 为消息标题
- body 为消息正文
- click 用户点击了消息之后，将触发此函数
- dismiss 消息消失或用户关闭消息时，将触发此函数

```js
let result = await horse.system.notify({
  title: "您收到新的消息",
  body: "此为消息的正文",
  click: () => {
    demoLog("用户点击了系统消息");
  },
  dismiss: () => {
    demoLog("系统通知消失了");
  },
});
```

使用默认浏览器打开外部连接

```javascript
horse.system.openExternal({
  target: "https://gitee.com/horsejs/horsejs#%E6%96%87%E6%A1%A3",
  workingDir: "",
});
```
