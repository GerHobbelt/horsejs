# 方法

## 弹出菜单

- data 为一个数组，数字里的内容是菜单项

```js
let data = [
  { name: "test1", tip: "测试测试" },
  { name: "测试测试", tip: "test2" },
];
let result = await horse.menu.popup({ data });
```
