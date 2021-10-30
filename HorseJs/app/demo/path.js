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
    console.log(result);
  },
  getDesktopPath: async () => {
    let result = await horse.path.getPath({
      name: "desktop",
    });
    console.log(result);
  },
  getAppDataPath: async () => {
    let result = await horse.path.getPath({
      name: "appData",
    });
    console.log(result);
  },
  getExePath: async () => {
    let result = await horse.path.getPath({
      name: "exePath",
    });
    console.log(result);
  },
  getTempPath: async () => {
    let result = await horse.path.getPath({
      name: "temp",
    });
    console.log(result);
  },
  getDirName: async () => {
    let result = await horse.path.getPath({
      name: "exePath",
    });
    let data = horse.path.dirName(result.data);
    console.log(data);
  },
  getExtName: async () => {
    let result = await horse.path.getPath({
      name: "exePath",
    });
    let data = horse.path.extName(result.data);
    console.log(data);
  },
};
