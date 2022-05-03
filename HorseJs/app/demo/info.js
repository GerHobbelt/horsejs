export let processor = {
  getAppInfo: async () => {
    let result = await horse.info.getAppInfo();
    demoLog(result);
  },
  getHorseInfo: async () => {
    let result = await horse.info.getHorseInfo();
    demoLog(result);
  },
  getOSInfo: async () => {
    let result = await horse.info.getOSInfo();
    demoLog(result);
  },
  getHardwareInfo: async () => {
    let result = await horse.info.getHardwareInfo();
    demoLog(result);
  },
  getNetInfo: async () => {
    let result = await horse.info.getNetInfo();
    demoLog(result);
  },
  getUserInfo: async () => {
    let result = await horse.info.getUserInfo();
    demoLog(result);
  },
};
