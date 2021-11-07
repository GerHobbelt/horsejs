export let processor = {
  getDesktopPath: async () => {
    let result = await horse.info.getPath({
      name: "desktop",
    });
    if (result.success) {
      alert(JSON.stringify(result.data));
    } else {
      alert("error");
    }
  },
  getAppDataPath: async () => {
    let result = await horse.info.getPath({
      name: "appData",
    });
    if (result.success) {
      alert(JSON.stringify(result.data));
    } else {
      alert("error");
    }
  },
  getExePath: async () => {
    let result = await horse.info.getPath({
      name: "exePath",
    });
    if (result.success) {
      alert(JSON.stringify(result.data));
    } else {
      alert("error");
    }
  },
  getExeFolder: async () => {
    let result = await horse.info.getPath({
      name: "exeFolder",
    });
    if (result.success) {
      alert(JSON.stringify(result.data));
    } else {
      alert("error");
    }
  },
};
