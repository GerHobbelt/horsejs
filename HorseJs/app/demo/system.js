export let processor = {
  setAutoStart: async () => {
    let result = await horse.system.autoStart({
      setOrRemove: "set",
    });
    demoLog(result);
  },
  removeAutoStart: async () => {
    let result = await horse.system.autoStart({
      setOrRemove: "remove",
    });
    demoLog(result);
  },
  setProtocol: async () => {
    let result = await horse.system.protocolClient({
      protocolName: "horse",
      setOrRemove: "set",
    });
    demoLog(result);
  },
  removeProtocol: async () => {
    let result = await horse.system.protocolClient({
      protocolName: "horse",
      setOrRemove: "remove",
    });
    demoLog(result);
  },
};
