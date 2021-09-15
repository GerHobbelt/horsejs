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
    document
      .querySelector("#windowSizeChangeBtn")
      .addEventListener("click", this.windowSizeChange);
    document
      .querySelector("#hideShowWindowBtn")
      .addEventListener("click", this.hideShowWindow);
    document
      .querySelector("#maximizeWindowBtn")
      .addEventListener("click", this.maximizeWindow);
    document
      .querySelector("#restoreWindowBtn")
      .addEventListener("click", this.restoreWindow);
    document
      .querySelector("#minimizeWindowBtn")
      .addEventListener("click", this.minimizeWindow);
    document
      .querySelector("#closeWindowBtn")
      .addEventListener("click", this.closeWindow);
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
