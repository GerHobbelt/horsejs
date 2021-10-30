let $ = (selector) => document.querySelector(selector);
export let dialogLogic = {
  openFile: async function () {
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
  openMultiFile: async function () {
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
  openFolder: function () {
    horse.window.hide();
    setTimeout(() => {
      horse.window.show();
    }, 3000);
  },
  init: function () {
    $("#openFileBtn").addEventListener("click", this.openFile);
    $("#openMultiFileBtn").addEventListener("click", this.openMultiFile);
    $("#openFolderBtn").addEventListener("click", this.openFolder);
  },
};
