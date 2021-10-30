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
};
