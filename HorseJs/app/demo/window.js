export let processor = {
  windowSizeChange: async () => {
    let result = await horse.window.resize({ width: 800, height: 600 });
    demoLog(result);
  },
  hideShowWindow: async () => {
    let result = await horse.window.hide();
    setTimeout(() => {
      horse.window.show();
    }, 3000);
    demoLog(result);
  },
  maximizeWindow: async () => {
    let result = await horse.window.maximize();
    demoLog(result);
  },
  restoreWindow: async () => {
    let result = await horse.window.restore();
    demoLog(result);
  },
  minimizeWindow: async () => {
    let result = await horse.window.minimize();
    demoLog(result);
  },
  closeWindow: async () => {
    let result = await horse.window.close();
    demoLog(result);
  },
  centerWindow: async () => {
    let result = await horse.window.center();
    demoLog(result);
  },
};
