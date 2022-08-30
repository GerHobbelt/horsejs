# 弹出菜单

- data 为一个数组，数组里的内容是菜单项
  - name 为菜单名称
  - id 为菜单 id，菜单 id 必须为数字，不能重复
  - type 为菜单类型，字符串，可能的值为：text，check，separator，默认值为 text
  - subMenu 为子菜单，子菜单是数组类型，数组项具备的属性亦为 name,id,type,subMenu，可以无限分级
- position 是菜单显示的位置，此项数据可以不提供，不提供时，菜单显示在鼠标所在的位置
- click 用户点击菜单时，将触发此函数，此函数的传入参数 index 为用户选择的第几个菜单

```js
let data = [
  { name: "test1", id: 0 },
  { name: "测试测试", id: 10 },
];
let result = await horse.menu.popup({
  data,
  position: { x: 200, y: 300 },
  click: (index) => {
    demoLog(`你点击了第${index}个菜单`);
  },
});
```
