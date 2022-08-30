export let processor = {
  windowSizeChange: () => {
    horse.window.resize({ width: 800, height: 600 });
  },
  hideShowWindow: () => {
    horse.window.hide();
    setTimeout(() => {
      horse.window.show();
    }, 3000);
  },
  maximizeWindow: () => {
    horse.window.maximize();
  },
  restoreWindow: () => {
    horse.window.restore();
  },
  minimizeWindow: () => {
    horse.window.minimize();
  },
  closeWindow: () => {
    horse.window.close();
  },
};
