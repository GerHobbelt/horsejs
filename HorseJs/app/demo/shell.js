export let processor = {
  openUrlWithDefaultBrowser() {
    horse.shell.openExternal({
      target: "https://gitee.com/horsejs/horsejs",
      workingDir: "",
    });
  },
};
