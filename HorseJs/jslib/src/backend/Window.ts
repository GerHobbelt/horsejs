import { BaseObject } from './BaseObject'
import { WindowConfig } from './WindowConfig'
import { ViewConfig } from './ViewConfig'
export class Window extends BaseObject {
  private createMsg(actionName: string, params?: any) {
    let msg = {
      className: Window.name,
      actionName,
      __winId: this.id,
      params,
    }
    return msg
  }
  static async createWindow(config: WindowConfig): Promise<Window> {
    let msg = {
      className: Window.name,
      actionName: this.createWindow.name,
      params: config,
    }
    let obj: any = await BaseObject.sendMsgToBrowser(msg)
    console.log('new window id:', obj.id)
    let result = new Window(obj.id)
    return result
  }
  async addView(config: ViewConfig) {
    let msg = this.createMsg(this.addView.name, config)
    await BaseObject.sendMsgToBrowser(msg)
  }
  async hide() {
    let msg = this.createMsg(this.hide.name)
    await BaseObject.sendMsgToBrowser(msg)
  }
  async show() {
    let msg = this.createMsg(this.show.name)
    await BaseObject.sendMsgToBrowser(msg)
  }
  async hideAllBrowserView() {}
  async hideBrowserView() {}
  async resize() {}
  async center() {}

  private constructor(id: number) {
    super(id)
  }
}
