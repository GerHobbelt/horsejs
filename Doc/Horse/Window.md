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
horse.window.addEventListener("maximized", () => {
  //your window is maximized
});
```

- 窗口最小化

```javascript
horse.window.addEventListener("minimized", () => {
  //your window is minimized
});
```
