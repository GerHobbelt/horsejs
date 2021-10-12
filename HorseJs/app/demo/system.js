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
  sendNotify: async () => {
    let result = await horse.system.notify({
      title: "您收到新的消息",
      body: "此为消息的正文",
      click: () => {
        demoLog("用户点击了系统消息");
      },
      dismiss: () => {
        demoLog("系统通知小时了");
      },
    });
    demoLog(result);
  },
};
