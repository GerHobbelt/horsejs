import { BaseObject } from './BaseObject'
import { WindowConfig } from './WindowConfig'
import { WindowMultiViewsConfig } from './controller/windowConfig/WindowMultiViewsConfig'
import { browserMessageChannel } from './browserMessageChannel'
import { BrowserViewConfig } from './BrowserViewConfig'
export class Window extends BaseObject {
  static async createWindow(config: WindowConfig): Promise<Window> {
    let msg = {
      className: Window.name,
      actionName: this.createWindow.name,
      params: config,
    }
    let obj: any = await BaseObject.sendMsgToBrowser(msg)
    let result = new Window(obj.id)
    return result
  }
  static createWindowMultiView(config: WindowMultiViewsConfig) {
    let msg = {
      className: Window.name,
      actionName: this.createWindowMultiView.name,
      params: config,
    }
    browserMessageChannel.sendMessage(msg)
  }
  async addViewOverlay(config: BrowserViewConfig) {
    let msg = {
      className: Window.name,
      actionName: this.addViewOverlay.name,
      __winId: this.id,
      params: config,
    }
    await BaseObject.sendMsgToBrowser(msg)
  }
  private constructor(id: number) {
    super(id)
  }
}
