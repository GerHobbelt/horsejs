export let processor = {
  openFile: async () => {
    let result = await horse.dialog.openFile({
      title: "test",
      defaultFilePath: "C:\\AMD",
      multiSelections: false,
      filters: ["*"],
      lastFilterIndex: 0,
    });
    if (result.success) {
      alert(JSON.stringify(result.data));
    } else {
      alert("error");
    }
  },
  openMultiFile: async () => {
    let result = await horse.dialog.openFile({
      title: "test",
      defaultFilePath: "C:\\AMD",
      multiSelections: true,
      filters: ["*"],
      lastFilterIndex: 0,
    });
    if (result.success) {
      alert(JSON.stringify(result.data));
    } else {
      alert("error");
    }
  },
  openFolder: () => {
    horse.window.hide();
    setTimeout(() => {
      horse.window.show();
    }, 3000);
  },
};
