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
   * 移除View
   * todo 这个方法有问题，BrowserView的进程没办法退出，这是CEF的问题
   * https://www.magpcss.org/ceforum/viewtopic.php?f=6&t=19152
   * https://bitbucket.org/chromiumembedded/cef/pull-requests/526
   * @param config
   * @returns
   */
  async removeView(view: View) {
    let msg = this.createMsg(this.removeView.name, { viewId: view.id });
    await BaseObject.sendMsgToBrowser(msg);
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
  /**
   * 设置窗口大小
   * @param param
   */
  async setSize(param: { width: number; height: number }) {
    let msg = this.createMsg(this.setSize.name, param);
    await BaseObject.sendMsgToBrowser(msg);
  }
  /**
   * 把窗口设置到屏幕中央
   */
  async center() {
    let msg = this.createMsg(this.center.name);
    await BaseObject.sendMsgToBrowser(msg);
  }
  /**
   * 把窗口设置到屏幕中央，同时设置窗口的大小
   * @param param
   */
  async centerAndSize(param: { width: number; height: number }) {
    let msg = this.createMsg(this.centerAndSize.name, param);
    await BaseObject.sendMsgToBrowser(msg);
  }
  /**
   * 设置窗口的位置
   * @param param
   */
  async setPosiion(param: { x: number; y: number }) {
    let msg = this.createMsg(this.setPosiion.name, param);
    await BaseObject.sendMsgToBrowser(msg);
  }
  /**
   * 设置窗口的大小和位置
   * @param param
   */
  async setPositionAndSize(param: { x: number; y: number; width: number; height: number }) {
    let msg = this.createMsg(this.setPositionAndSize.name, param);
    await BaseObject.sendMsgToBrowser(msg);
  }
  /**
   * 设置窗口的标题
   * @param title
   */
  async setTitle(title: string) {
    let msg = this.createMsg(this.setTitle.name, { title });
    await BaseObject.sendMsgToBrowser(msg);
  }
  private constructor(id: number) {
    super(id);
  }
}
