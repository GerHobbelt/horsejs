export let processor = {
  setAutoStart: async () => {
    let result = await horse.system.setAutoStart({
      setOrRemove: "set",
    });
    demoLog(result);
  },
  removeAutoStart: async () => {
    let result = await horse.system.setAutoStart({
      setOrRemove: "remove",
    });
    demoLog(result);
  },
};
