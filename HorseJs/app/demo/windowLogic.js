export let windowLogic = {
  windowSizeChange: function () {
    alert(1);
  },
  init: function () {
    document
      .querySelector("#windowSizeChangeBtn")
      .addEventListener("click", () => this.windowSizeChange());

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
