export let processor = {
  getDesktopPath: async () => {
    let result = await horse.info.getPath({
      name: "desktop",
    });
    demoLog(result);
  },
  getAppDataPath: async () => {
    let result = await horse.info.getPath({
      name: "appData",
    });
    demoLog(result);
  },
  getExePath: async () => {
    let result = await horse.info.getPath({
      name: "exePath",
    });
    demoLog(result);
  },
  getExeFolder: async () => {
    let result = await horse.info.getPath({
      name: "exeFolder",
    });
    demoLog(result);
  },
  getAppInfo: async () => {
    let result = await horse.info.getAppInfo();
    demoLog(result);
  },
  getHorseInfo: async () => {
    let result = await horse.info.getHorseInfo();
    demoLog(result);
  },
};
