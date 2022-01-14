export let processor = {
  readDir: async () => {
    let folderResult = await horse.dialog.openFolder({
      title: "请你先选择一个目录~~~",
      defaultFilePath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      lastFilterIndex: 0,
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
  getExeFolder: async () => {
    let result = await horse.path.getPath({
      name: "exeFolder",
    });
    demoLog(result);
  },
};
