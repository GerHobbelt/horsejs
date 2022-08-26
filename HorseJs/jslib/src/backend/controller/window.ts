import { browserMessageChannel } from '../messageChannel/browserMessageChannel'
export class Window {
  createWindow(config: any) {
    let msg = {
      className: Window.name,
      actionName: this.createWindow.name,
      params: config,
    }
    console.log(msg)
    browserMessageChannel.sendMessage(msg)
  }
}
