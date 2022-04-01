# 托盘图标

- data 为一个数组，数字里的内容是菜单项
- position 是菜单显示的位置，此项数据可以不提供，不提供时，菜单显示在鼠标所在的位置
- click 用户点击菜单时，将触发此函数，此函数的传入参数 index 为用户选择的第几个菜单

```js
let data = [{ name: "test1" }, { name: "测试测试" }];
let result = await horse.menu.popup({
  data,
  position: { x: 200, y: 300 },
  click: (index) => {
    demoLog(`你点击了第${index}个菜单`);
  },
});
```
