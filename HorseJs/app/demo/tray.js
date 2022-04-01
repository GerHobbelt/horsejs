export let processor = {
  create: async () => {
    let menu = [{ name: "test1" }, { name: "测试测试" }, { name: "测试测试" }];
    let result = await horse.tray.create({
      iconPath: "D:\\project\\horsejs\\x64\\Debug\\icon.ico",
      tip: "这是图标提示",
      menu,
      menuClick: (index) => {
        demoLog(`你点击了第${index}个菜单`);
      },
      trayClick: (clickType) => {
        demoLog("托盘图标事件：", clickType);
      },
    });
    demoLog(result);
  },
  resetIcon: async () => {
    let data = [{ name: "test1" }, { name: "测试测试" }, { name: "测试测试" }];
    let result = await horse.tray.popup({
      data,
      click: (index) => {
        demoLog(`你点击了第${index}个菜单`);
      },
    });
    demoLog(result);
  },
  destroy: async () => {
    let result = await horse.tray.destroy();
    demoLog(result);
  },
};
