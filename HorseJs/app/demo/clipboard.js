export let processor = {
  getClipboardText: async () => {
    let result = await horse.clipboard.getData({ dataType: "text" });
    if (result.success) {
      alert(JSON.stringify(result.data));
    } else {
      alert("error");
    }
  },
};
