# 窗口控制

## 方法

- 最大化当前窗口

```javascript
horse.window.maximize();
```

- 最小化当前窗口

```javascript
horse.window.minimize();
```

- 还原窗口

```javascript
horse.window.restore();
```

- 关闭窗口

```javascript
horse.window.close();
```

- 隐藏窗口

```javascript
horse.window.hide();
```

- 显示窗口

```javascript
horse.window.show();
```

- 改变窗口大小

```javascript
horse.window.resize(width, height);
```

## 事件

- 窗口最大化

```javascript
horse.window.addEventListener("maximize", () => {
  //your code
});
```

- 取消窗口最大化

```javascript
horse.window.addEventListener("unMaximize", () => {
  //your code
});
```

- 窗口隐藏

窗口最小化时也会触发窗口隐藏事件

```javascript
horse.window.addEventListener("hide", () => {
  //your code
});
```

- 窗口显示

```javascript
horse.window.addEventListener("show", () => {
  //your code
});
```

- 移除事件监听

如果开发者没有提供第二个参数，将会移除所有关于 eventName 的事件监听

eventName 可能的值为 show、hide、unMaximize 等

```javascript
horse.window.removeEventListener(eventName, yourFunction);
```
