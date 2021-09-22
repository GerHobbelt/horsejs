export let processor = {
  openFile: async () => {
    let result = await horse.dialog.openFile({
      title: "test",
      defaultFilePath: "C:\\AMD",
      multiSelections: false,
      filters: ["*"],
      lastFilterIndex: 0,
    });
    demoLog(result);
  },
  openMultiFile: async () => {
    let result = await horse.dialog.openFile({
      title: "test",
      defaultFilePath: "C:\\AMD",
      multiSelections: true,
      filters: ["*"],
      lastFilterIndex: 0,
    });
    demoLog(result);
  },
  openFolder: async () => {
    let result = await horse.dialog.openFolder({
      title: "test",
      defaultFilePath: "C:\\AMD",
      multiSelections: true,
      filters: ["*"],
      lastFilterIndex: 0,
    });
    demoLog(result);
  },
};
