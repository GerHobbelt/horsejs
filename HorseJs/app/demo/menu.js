export let processor = {
  popup: async () => {
    let data = [
      { name: "test1", tip: "测试测试" },
      { name: "测试测试", tip: "test2" },
      { name: "测试测试", tip: "test2" },
    ];
    let result = await horse.menu.popup({
      data,
      click: (index) => {
        demoLog(`你点击了第${index}个菜单`);
      },
    });
    demoLog(result);
  },
  popupAtPoint: async () => {
    let data = [
      { name: "test1", tip: "测试测试" },
      { name: "测试测试", tip: "test2" },
      { name: "测试测试", tip: "test2" },
    ];
    let result = await horse.menu.popup({
      data,
      position: { x: 200, y: 300 },
      click: (index) => {
        demoLog(`你点击了第${index}个菜单`);
      },
    });
    demoLog(result);
  },
};
