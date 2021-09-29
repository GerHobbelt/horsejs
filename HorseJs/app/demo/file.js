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
  readFileFromPosition: async () => {
    let folderResult = await horse.dialog.openFile({
      title: "请你先选择一个文件~~~",
      defaultFilePath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      lastFilterIndex: 0,
    });
    let result = await horse.file.readFileFromPosition({
      path: folderResult.data[0],
      bufferSize: 65536,
      position: 3,
    });
    demoLog(result);
  },
  writeFile: async () => {
    let folderResult = await horse.dialog.openFile({
      title: "请你先选择一个文件~~~",
      defaultFilePath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      lastFilterIndex: 0,
    });
    let result = await horse.file.writeFile({
      path: folderResult.data[0],
      data: `
      你好，世界
      안녕 세계
      Hello World
      `,
      existThen: "append",
    });
    demoLog(result);
  },
  writeFileCreate: async () => {
    let folderResult = await horse.dialog.openFolder({
      title: "请你先选择一个目录~~~",
      defaultFilePath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      lastFilterIndex: 0,
    });
    let name = Math.floor(Math.pow(10, 6) * Math.random());
    let path = folderResult.data[0] + `/${name}.txt`;
    let result = await horse.file.writeFile({
      path,
      data: `
      你好，世界
      안녕 세계
      Hello World
      `,
      existThen: "append",
      notExistThen: "create",
    });
    demoLog(result);
  },
  copyFile: async () => {
    let srcResult = await horse.dialog.openFile({
      title: "请选择待拷贝的文件",
      defaultFilePath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      lastFilterIndex: 0,
    });
    let destResult = await horse.dialog.openFolder({
      title: "请选择拷贝目标目录",
      defaultFilePath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      lastFilterIndex: 0,
    });
    let src = srcResult.data[0];
    let baseName = horse.path.baseName(src);
    let dest = destResult.data[0] + baseName;
    await horse.file.copy({ src, dest });
    demoLog(result);
  },
};
