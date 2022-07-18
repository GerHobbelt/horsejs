export let processor = {
  getAppInfo: async () => {
    let result = await horse.info.getAppInfo();
    console.log(result);
  },
  getHorseInfo: async () => {
    let result = await horse.info.getHorseInfo();
    console.log(result);
  },
  getOSInfo: async () => {
    let result = await horse.info.getOSInfo();
    console.log(result);
  },
  getHardwareInfo: async () => {
    let result = await horse.info.getHardwareInfo();
    console.log(result);
  },
  getNetInfo: async () => {
    let result = await horse.info.getNetInfo();
    console.log(result);
  },
  getUserInfo: async () => {
    let result = await horse.info.getUserInfo();
    console.log(result);
  },
};
