export let processor = {
  getLastWriteTime: async () => {
    let fileResult = await horse.dialog.openFile({
      title: "请你先选择一个文件~~~",
      defaultPath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      filterIndex: 0,
    });
    let result = await horse.file.getLastWriteTime({
      path: fileResult.data[0],
    });
    console.log(result);
  },
  getFileSize: async () => {
    let folderResult = await horse.dialog.openFile({
      title: "请你先选择一个文件~~~",
      defaultPath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      filterIndex: 0,
    });
    let result = await horse.file.getFileSize({ path: folderResult.data[0] });
    console.log(result);
  },
  readFile: async () => {
    let folderResult = await horse.dialog.openFile({
      title: "请你先选择一个文件~~~",
      defaultPath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      filterIndex: 0,
    });
    let decoder = new TextDecoder("utf-8");
    let result = await horse.file.readFile({
      path: folderResult.data[0],
      bufferSize: 65536,
      onData: (chunk) => {
        let fileData = decoder.decode(chunk);
        console.log("文件数据片：", fileData);
      },
      onDataFinish: (result) => {
        console.log("读取文件完成：", result);
      },
    });
    console.log("请求读取文件：", result);
  },
  readFileFromPosition: async () => {
    let folderResult = await horse.dialog.openFile({
      title: "请你先选择一个文件~~~",
      defaultPath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      filterIndex: 0,
    });
    let decoder = new TextDecoder("utf-8");
    let result = await horse.file.readFileFromPosition({
      path: folderResult.data[0],
      bufferSize: 65536,
      position: 6,
      onData: (chunk) => {
        let fileData = decoder.decode(chunk);
        console.log("文件数据片：", fileData);
      },
      onDataFinish: (result) => {
        console.log("读取文件完成：", result);
      },
    });
    console.log(result);
  },
  writeFile: async () => {
    let folderResult = await horse.dialog.openFile({
      title: "请你先选择一个文件~~~",
      defaultPath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      filterIndex: 0,
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
    console.log(result);
  },
  writeFileCreate: async () => {
    let folderResult = await horse.dialog.openFolder({
      title: "请你先选择一个目录~~~",
      defaultPath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      filterIndex: 0,
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
    console.log(result);
  },
  copyFile: async () => {
    let srcResult = await horse.dialog.openFile({
      title: "请选择待拷贝的文件",
      defaultPath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      filterIndex: 0,
    });
    let destResult = await horse.dialog.openFolder({
      title: "请选择拷贝目标目录",
      defaultPath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      filterIndex: 0,
    });
    let src = srcResult.data[0];
    let baseName = horse.path.baseName(src);
    let dest = destResult.data[0] + baseName;
    await horse.file.copy({ src, dest });
    console.log(result);
  },
};
