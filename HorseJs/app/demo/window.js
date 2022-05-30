export let processor = {
  windowSizeChange: async () => {
    let result = await horse.window.resize({ width: 800, height: 600 });
    console.log(result);
  },
  hideShowWindow: async () => {
    let result = await horse.window.hide();
    setTimeout(() => {
      horse.window.show();
    }, 3000);
    console.log(result);
  },
  maximizeWindow: async () => {
    let result = await horse.window.maximize();
    console.log(result);
  },
  restoreWindow: async () => {
    let result = await horse.window.restore();
    console.log(result);
  },
  minimizeWindow: async () => {
    let result = await horse.window.minimize();
    console.log(result);
  },
  closeWindow: async () => {
    let result = await horse.window.close();
    console.log(result);
  },
  centerWindow: async () => {
    let result = await horse.window.center();
    console.log(result);
  },
  openDevTool: async () => {
    let result = await horse.window.openDevTool();
    console.log(result);
  },
};
