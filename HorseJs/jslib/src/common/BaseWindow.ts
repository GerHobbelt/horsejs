import { WindowConfig } from './WindowConfig';
import { ViewConfig } from './ViewConfig';
import { BaseView } from './BaseView';
import EventEmitter from 'eventemitter3';
export class BaseWindow extends EventEmitter {
  id: number;
  view: BaseView;
  private prepareMsg(actionName: string, msg: any) {
    let result = {
      __className: 'Win',
      __actionName: actionName,
      __winId: this.id,
    };
    Object.assign(result, msg);
    return result;
  }
  /**
   * 创建窗口，静态方法
   * @param param
   * @returns
   */
  static async createWindow(param: WindowConfig): Promise<BaseWindow> {
    let msg = {
      __className: 'Win',
      __actionName: this.createWindow.name,
    };
    Object.assign(msg, param);
    let obj: any = await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
    let result = new BaseWindow(obj.winId);
    result.view = BaseView.__createView(obj.viewId);
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
  async addOverlayView(param: ViewConfig): Promise<BaseView> {
    let msg = this.prepareMsg(this.addOverlayView.name, param);
    let obj: any = await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
    let result = BaseView.__createView(obj.id);
    return result;
  }

  /**
   * 获取窗口所有的
   * @returns
   */
  async getOverlayView(): Promise<BaseView[]> {
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
  async removeView(view: BaseView) {
    let msg = this.prepareMsg(this.removeView.name, { viewId: view.id });
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }
  /**
   * 隐藏窗口
   */
  async hide() {
    let msg = this.prepareMsg('setVisible', { visible: false });
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }
  /**
   * 显示窗口
   */
  async show() {
    let msg = this.prepareMsg('setVisible', { visible: true });
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }
  /**
   * 最小化窗口
   */
  async minimize() {
    let msg = this.prepareMsg(this.minimize.name, {});
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }
  /**
   * 最大化窗口
   */
  async maximize() {
    let msg = this.prepareMsg(this.maximize.name, {});
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }

  /**
   * 关闭窗口
   */
  async close() {
    let msg = this.prepareMsg(this.close.name, {});
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }

  /**
   * 还原窗口
   */
  async restore() {
    let msg = this.prepareMsg(this.restore.name, {});
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
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
    let msg = this.prepareMsg('positionAndSize', param);
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }
  /**
   * 把窗口设置到屏幕中央
   */
  async center() {
    let msg = this.prepareMsg('centerAndSize', {});
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }
  /**
   * 把窗口设置到屏幕中央，同时设置窗口的大小
   * @param param
   */
  async centerAndSize(param: { width: number; height: number }) {
    let msg = this.prepareMsg(this.centerAndSize.name, param);
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }
  /**
   * 设置窗口的位置
   * @param param
   */
  async position(param: { x: number; y: number }) {
    let msg = this.prepareMsg('positionAndSize', param);
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }
  /**
   * 设置窗口的大小和位置
   * @param param
   */
  async positionAndSize(param: { x: number; y: number; width: number; height: number }) {
    let msg = this.prepareMsg(this.positionAndSize.name, param);
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }
  /**
   * 获取窗口的位置和大小
   * @returns
   */
  async getBound() {
    let msg = this.prepareMsg(this.getBound.name, {});
    let result = await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
    return result.result;
  }
  /**
   * 设置窗口的标题
   * @param title
   */
  async setTitle(title: string) {
    let msg = this.prepareMsg(this.setTitle.name, { title });
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }
  protected constructor(id: number) {
    super();
    this.id = id;
  }
}
