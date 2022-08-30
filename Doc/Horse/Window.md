# 最大化当前窗口

```javascript
await horse.window.maximize();
```

# 最小化当前窗口

```javascript
await horse.window.minimize();
```

# 还原窗口

```javascript
await horse.window.restore();
```

# 关闭窗口

```javascript
await horse.window.close();
```

# 隐藏窗口

```javascript
await horse.window.hide();
```

# 显示窗口

```javascript
await horse.window.show();
```

# 改变窗口大小

```javascript
await horse.window.resize({ width: 800, height: 600 });
```

# 移动窗口到屏幕中央

```javascript
await horse.window.center();
```

# 打开当前窗口的开发者调试工具

多次调用并不会打开多个开发者调试工具

```javascript
let result = await horse.window.openDevTool();
```

# 关闭当前窗口的开发者调试工具

即使从没打开过开发者调试工具，调用该方法也不会产生任何异常

```javascript
let result = await horse.window.openDevTool();
```

# 窗口最大化事件

```javascript
horse.window.addEventListener("maximize", () => {
  //your code
});
```

# 取消窗口最大化事件

```javascript
horse.window.addEventListener("unMaximize", () => {
  //your code
});
```

# 窗口隐藏事件

窗口最小化时也会触发窗口隐藏事件

```javascript
horse.window.addEventListener("hide", () => {
  //your code
});
```

# 窗口显示事件

```javascript
horse.window.addEventListener("show", () => {
  //your code
});
```

# 移除事件监听

如果开发者没有提供第二个参数，将会移除所有关于 eventName 的事件监听

eventName 可能的值为 show、hide、unMaximize 等

```javascript
horse.window.removeEventListener(eventName, yourFunction);
```
