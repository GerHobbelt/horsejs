export let processor = {
  getClipboardText: async () => {
    let result = await horse.clipboard.getData({ dataType: "text" });
    demoLog(result);
  },
};
