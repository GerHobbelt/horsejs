let $ = (selector) => document.querySelector(selector);
export let windowLogic = {
  windowSizeChange: function () {
    horse.window.resize({ width: 800, height: 600 });
  },
  hideShowWindow: function () {
    horse.window.hide();
    setTimeout(() => {
      horse.window.show();
    }, 3000);
  },
  maximizeWindow: function () {
    horse.window.maximize();
  },
  restoreWindow: function () {
    horse.window.restore();
  },
  minimizeWindow: function () {
    horse.window.minimize();
  },
  closeWindow: function () {
    horse.window.close();
  },
  init: function () {
    $("#windowSizeChangeBtn").addEventListener("click", this.windowSizeChange);
    $("#hideShowWindowBtn").addEventListener("click", this.hideShowWindow);
    $("#maximizeWindowBtn").addEventListener("click", this.maximizeWindow);
    $("#restoreWindowBtn").addEventListener("click", this.restoreWindow);
    $("#minimizeWindowBtn").addEventListener("click", this.minimizeWindow);
    $("#closeWindowBtn").addEventListener("click", this.closeWindow);
    // document
    // .querySelector("#openFileBtn")
    // .addEventListener("click", async () => {
    //   let result = await horse.dialog.openFile({
    //     title: "test",
    //     defaultFilePath: "C:\\AMD",
    //     filters: ["*"],
    //     lastFilterIndex: 0,
    //   });
    //   console.log(JSON.stringify(result));
    // });
  },
};
