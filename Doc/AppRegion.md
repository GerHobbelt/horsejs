# 可拖拽区域

默认情况下，HorseJs 创建的窗口是没有标题栏的，需要开发者自己定义标题栏。

开发者可以通过如下样式来指定标题栏的可拖拽区域

```css
-webkit-app-region: drag;
```

如果开发者希望可拖拽区域中的某些元素不可拖拽
可以使用如下样式来修饰这些元素

```css
-webkit-app-region: no-drag;
```

这些配置与 Electron 或 NW.js 是一致的。
