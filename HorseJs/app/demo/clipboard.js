export let processor = {
  getClipboardText: async () => {
    let result = await horse.clipboard.getData({ dataType: "text" });
    demoLog(result);
  },
  getClipboardFile: async () => {
    let result = await horse.clipboard.getData({ dataType: "file" });
    demoLog(result);
  },
  getClipboardHTML: async () => {
    let result = await horse.clipboard.getData({ dataType: "html" });
    demoLog(result);
  },
  setClipboardText: async () => {
    let result = await horse.clipboard.setData({
      dataType: "text",
      data: "此文本被写入剪切板",
    });
    demoLog(result);
  },
  setClipboardFile: async () => {
    let fileResult = await horse.dialog.openFile({
      title: "test",
      defaultPath: "C:\\AMD",
      multiSelections: true,
      filters: ["*"],
      filterIndex: 0,
    });
    let result = await horse.clipboard.setData({
      dataType: "file",
      data: fileResult.data,
    });
    demoLog(result);
  },
  setClipboardHTML: async () => {
    let result = await horse.clipboard.setData({
      dataType: "html",
      data: `<span style="color:red">此HTML被写入剪切板</span>`,
    });
    demoLog(result);
  },
};
