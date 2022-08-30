export let processor = {
  readDir: async () => {
    let folderResult = await horse.dialog.openFolder({
      title: "请你先选择一个目录~~~",
      defaultPath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      filterIndex: 0,
    });
    let result = await horse.path.readDir({ path: folderResult.data[0] });
    demoLog(result);
  },
  getDesktopPath: async () => {
    let result = await horse.path.getPath({
      name: "desktop",
    });
    demoLog(result);
  },
  getAppDataPath: async () => {
    let result = await horse.path.getPath({
      name: "appData",
    });
    demoLog(result);
  },
  getExePath: async () => {
    let result = await horse.path.getPath({
      name: "exePath",
    });
    demoLog(result);
  },
  getTempPath: async () => {
    let result = await horse.path.getPath({
      name: "temp",
    });
    demoLog(result);
  },
  getDirName: async () => {
    let result = await horse.path.getPath({
      name: "exePath",
    });
    let data = horse.path.dirName(result.data);
    demoLog(data);
  },
  getExtName: async () => {
    let result = await horse.path.getPath({
      name: "exePath",
    });
    let data = horse.path.extName(result.data);
    demoLog(data);
  },
};
