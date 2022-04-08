# 托盘图标

## 创建托盘图标

目前一个应用程序仅允许注册一个托盘图标

- menu 为一个数组，数组里的内容是菜单项
- tip 为鼠标移到托盘图标上面是显示的提示信息
- iconPath 为托盘图标的路径，目前 Windows 操作系统下只支持 ico 格式的文件
- menuClick 为点击托盘图标菜单时的回调函数，index 为点击的第几项菜单，从 0 开始计数
- leftButtonDown 为鼠标左键在托盘图标上按下时的回调函数
- leftButtonDoubleClick 为鼠标左键在托盘图标上双击时的回调函数
- leftButtonUp 为鼠标左键在托盘图标上弹起时的回调函数
- rightButtonDown 为鼠标右键在托盘图标上按下时的回调函数
- rightButtonDoubleClick 为鼠标右键在托盘图标上双击时的回调函数
- rightButtonUp 为鼠标右键在托盘图标上弹起时的回调函数
- mouseMove 为鼠标在托盘图标上移动时的回调函数

```js
let menu = [{ name: "test1" }, { name: "测试测试" }, { name: "测试测试" }];
let exePath = await horse.path.getPath({ name: "exePath" });
let iconPath = horse.path.dirName(exePath.data) + "\\icon.ico"; //todo
let result = await horse.tray.create({
  iconPath,
  tip: "这是图标提示",
  menu,
  menuClick: (index) => {
    console.log(`你点击了第${index}个菜单`);
  },
  leftButtonDown: () => {
    console.log("托盘图标事件");
  },
});
```

## 销毁托盘图标

```js
let result = await horse.tray.destroy();
```

## 切换托盘图标的图像

如果你创建托盘图标时设置了 tip，那么更换托盘图标时，也应该提供 tip，不然原先设置的 tip 将会小时

```js
let exePath = await horse.path.getPath({ name: "exePath" });
let iconPath = horse.path.dirName(exePath.data) + "\\icon2.ico"; //todo
let tip = `这是图标提示`;
let result = await horse.tray.resetIcon({ iconPath, tip });
```
