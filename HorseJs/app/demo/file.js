export let processor = {
  readDir: async () => {
    let folderResult = await horse.dialog.openFolder({
      title: "请你先选择一个目录~~~",
      defaultFilePath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      lastFilterIndex: 0,
    });
    let result = await horse.file.readDir({ path: folderResult.data[0] });
    demoLog(result);
  },
  getLastWriteTime: async () => {
    let fileResult = await horse.dialog.openFile({
      title: "请你先选择一个文件~~~",
      defaultFilePath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      lastFilterIndex: 0,
    });
    let result = await horse.file.getLastWriteTime({
      path: fileResult.data[0],
    });
    demoLog(result);
  },
  isFolder: async () => {
    let fileResult = await horse.dialog.openFile({
      title: "请你先选择一个文件~~~",
      defaultFilePath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      lastFilterIndex: 0,
    });
    let result = await horse.file.isFolder({
      path: fileResult.data[0],
    });
    demoLog(result);
  },
  getFileSize: async () => {
    let folderResult = await horse.dialog.openFile({
      title: "请你先选择一个文件~~~",
      defaultFilePath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      lastFilterIndex: 0,
    });
    let result = await horse.file.getFileSize({ path: folderResult.data[0] });
    demoLog(result);
  },
  readFile: async () => {
    let folderResult = await horse.dialog.openFile({
      title: "请你先选择一个文件~~~",
      defaultFilePath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      lastFilterIndex: 0,
    });
    let result = await horse.file.readFile({
      path: folderResult.data[0],
      bufferSize: 65536,
      onData: (data) => {
        demoLog(data);
      },
    });

    demoLog("文件读取完成", result);
  },
};
