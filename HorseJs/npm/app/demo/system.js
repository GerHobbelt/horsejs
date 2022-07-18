export let processor = {
  setAutoStart: async () => {
    let result = await horse.system.autoStart({
      setOrRemove: 'set',
    })
    console.log(result)
  },
  removeAutoStart: async () => {
    let result = await horse.system.autoStart({
      setOrRemove: 'remove',
    })
    console.log(result)
  },
  setProtocol: async () => {
    let result = await horse.system.protocolClient({
      protocolName: 'horse',
      setOrRemove: 'set',
    })
    console.log(result)
  },
  removeProtocol: async () => {
    let result = await horse.system.protocolClient({
      protocolName: 'horse',
      setOrRemove: 'remove',
    })
    console.log(result)
  },
  sendNotify: async () => {
    let result = await horse.system.notify({
      title: '您收到新的消息',
      body: '此为消息的正文',
      click: () => {
        console.log('用户点击了系统消息')
      },
      dismiss: () => {
        console.log('系统通知消失了')
      },
    })
    console.log(result)
  },
  openUrlWithDefaultBrowser() {
    horse.system.openExternal({
      target: 'https://gitee.com/horsejs/horsejs',
      workingDir: '',
    })
  },
}
