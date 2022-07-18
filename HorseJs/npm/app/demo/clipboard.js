export let processor = {
  getClipboardText: async () => {
    let result = await horse.clipboard.getData({ dataType: "text" });
    console.log(result);
  },
  getClipboardFile: async () => {
    let result = await horse.clipboard.getData({ dataType: "file" });
    console.log(result);
  },
  getClipboardHTML: async () => {
    let result = await horse.clipboard.getData({ dataType: "html" });
    console.log(result);
  },
  setClipboardText: async () => {
    let result = await horse.clipboard.setData({
      dataType: "text",
      data: "此文本被写入剪切板",
    });
    console.log(result);
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
    console.log(result);
  },
  setClipboardHTML: async () => {
    let result = await horse.clipboard.setData({
      dataType: "html",
      data: `<span style="color:red">此HTML被写入剪切板</span>`,
    });
    console.log(result);
  },
};
