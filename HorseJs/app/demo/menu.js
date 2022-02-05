export let processor = {
  popup: async () => {
    let data = [
      { name: "test1", tip: "测试测试" },
      { name: "测试测试", tip: "test2" },
      { name: "测试测试", tip: "test2" },
    ];
    let result = await horse.menu.popup({ data });
    demoLog(result);
  },
};
