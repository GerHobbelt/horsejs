export let processor = {
  readDir: async () => {
    let folderResult = await horse.dialog.openFolder({
      title: "请你先选择一个目录~~~",
      defaultFilePath: "C:\\",
      multiSelections: false,
      filters: ["*"],
      lastFilterIndex: 0,
    });
    let result = await horse.file.readDir({ folderPath: folderResult.data[0] });
    if (result.success) {
      alert(JSON.stringify(result.data));
    } else {
      alert("error");
    }
  },
};
