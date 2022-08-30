export let processor = {
  create: async () => {
    let menu = [{ name: "test1" }, { name: "测试测试" }, { name: "测试测试" }];
    let exePath = await horse.path.getPath({ name: "exePath" });
    let iconPath = horse.path.dirName(exePath.data) + "\\icon.ico"; //todo
    let result = await horse.tray.create({
      iconPath,
      tip: "这是图标提示",
      menu,
      menuClick: (index) => {
        demoLog(`你点击了第${index}个菜单`);
      },
      leftButtonDown: () => {
        demoLog("托盘图标事件");
      },
    });
    demoLog(result);
  },
  resetIcon: async () => {
    let exePath = await horse.path.getPath({ name: "exePath" });
    let iconPath = horse.path.dirName(exePath.data) + "\\icon2.ico"; //todo
    let tip = `这是图标提示`;
    let result = await horse.tray.resetIcon({ iconPath, tip });
    demoLog(result);
  },
  destroy: async () => {
    let result = await horse.tray.destroy();
    demoLog(result);
  },
};
