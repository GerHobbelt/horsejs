import { BaseObject } from './BaseObject';
import { WindowConfig } from './WindowConfig';
import { ViewConfig } from './ViewConfig';
import { View } from './View';
export class Window extends BaseObject {
  view: View;
  viewOverlay: View[] = [];
  private createMsg(actionName: string, params?: any) {
    let msg = {
      className: Window.name,
      actionName,
      __winId: this.id,
      params,
    };
    return msg;
  }
  /**
   * 创建窗口，静态方法
   * @param config
   * @returns
   */
  static async createWindow(config: WindowConfig): Promise<Window> {
    let msg = {
      className: Window.name,
      actionName: this.createWindow.name,
      params: config,
    };
    let obj: any = await BaseObject.sendMsgToBrowser(msg);
    let result = new Window(obj.id);
    result.view = View.__createView(0);
    return result;
  }
  /**
   * 为窗口添加view
   * @param config
   * @returns
   */
  async addView(config: ViewConfig): Promise<View> {
    let msg = this.createMsg(this.addView.name, config);
    let obj: any = await BaseObject.sendMsgToBrowser(msg);
    let result = View.__createView(obj.id);
    this.viewOverlay.push(result);
    return result;
  }
  /**
   * 隐藏窗口
   */
  async hide() {
    let msg = this.createMsg(this.hide.name);
    await BaseObject.sendMsgToBrowser(msg);
  }
  /**
   * 显示窗口
   */
  async show() {
    let msg = this.createMsg(this.show.name);
    await BaseObject.sendMsgToBrowser(msg);
  }
  /**
   * 隐藏所有的ViewOverlay
   */
  async hideAllViewOverlay() {}
  async resize() {}
  async center() {}
  async setTitle(title: string) {}
  async removeView(view: View) {}
  private constructor(id: number) {
    super(id);
  }
}
