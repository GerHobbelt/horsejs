import { BaseObject } from './BaseObject';
import { WindowConfig } from './WindowConfig';
import { ViewConfig } from './ViewConfig';
import { View } from './View';
export class BaseWindow extends BaseObject {
  view: View;
  private createMsg(actionName: string, params?: any) {
    let msg = {
      className: 'Window',
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
  static async createWindow(config: WindowConfig): Promise<BaseWindow> {
    let msg = {
      className: 'Window',
      actionName: this.createWindow.name,
      params: config,
    };
    let obj: any = await BaseObject.sendMsgToBrowser(msg);
    console.log(obj);
    let result = new BaseWindow(obj.winId);
    result.view = View.__createView(obj.viewId);
    return result;
  }
  /**
   * 根据Id获取Window对象，静态方法
   * @param id
   * @returns
   */
  static async getWindowById(id: number): Promise<BaseWindow | any> {
    //todo
    return null;
  }
  /**
   * 获取所有窗口，静态方法
   * @returns
   */
  static async getAllWindow(): Promise<BaseWindow[]> {
    //todo
    return [];
  }

  /**
   * 为窗口添加view
   * @param config
   * @returns
   */
  async addOverlayView(config: ViewConfig): Promise<View> {
    let msg = this.createMsg(this.addOverlayView.name, config);
    let obj: any = await BaseObject.sendMsgToBrowser(msg);
    let result = View.__createView(obj.id);
    return result;
  }

  /**
   * 获取窗口所有的
   * @returns
   */
  async getOverlayView(): Promise<View[]> {
    return [];
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
    let msg = this.createMsg('setVisible', { visible: false });
    await BaseObject.sendMsgToBrowser(msg);
  }
  /**
   * 显示窗口
   */
  async show() {
    let msg = this.createMsg('setVisible', { visible: true });
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
    let msg = this.createMsg('centerAndSize');
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
  async position(param: { x: number; y: number }) {
    let msg = this.createMsg('positionAndSize', param);
    await BaseObject.sendMsgToBrowser(msg);
  }
  /**
   * 设置窗口的大小和位置
   * @param param
   */
  async positionAndSize(param: { x: number; y: number; width: number; height: number }) {
    let msg = this.createMsg(this.positionAndSize.name, param);
    await BaseObject.sendMsgToBrowser(msg);
  }
  /**
   * 获取窗口的位置和大小
   * @returns
   */
  async getBound() {
    let msg = this.createMsg(this.getBound.name);
    let result = await BaseObject.sendMsgToBrowser(msg);
    return result.result;
  }
  /**
   * 设置窗口的标题
   * @param title
   */
  async setTitle(title: string) {
    let msg = this.createMsg(this.setTitle.name, { title });
    await BaseObject.sendMsgToBrowser(msg);
  }
  protected constructor(id: number) {
    super(id);
  }
}
