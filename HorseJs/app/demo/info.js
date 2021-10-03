export let processor = {
  getAppInfo: async () => {
    let result = await horse.info.getAppInfo();
    demoLog(result);
  },
  getHorseInfo: async () => {
    let result = await horse.info.getHorseInfo();
    demoLog(result);
  },
};
