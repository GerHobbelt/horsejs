export let processor = {
  create: async () => {
    alert(12);
    let menu = [{ name: "test1" }, { name: "测试测试" }, { name: "测试测试" }];
    let result = await horse.tray.create({
      iconPath: "",
      menu,
      menuClick: (index) => {
        demoLog(`你点击了第${index}个菜单`);
      },
    });
    demoLog(result);
  },
  reset: async () => {
    let data = [{ name: "test1" }, { name: "测试测试" }, { name: "测试测试" }];
    let result = await horse.menu.popup({
      data,
      click: (index) => {
        demoLog(`你点击了第${index}个菜单`);
      },
    });
    demoLog(result);
  },
  destroy: async () => {
    let data = [{ name: "test1" }, { name: "测试测试" }, { name: "测试测试" }];
    let result = await horse.menu.popup({
      data,
      click: (index) => {
        demoLog(`你点击了第${index}个菜单`);
      },
    });
    demoLog(result);
  },
};
