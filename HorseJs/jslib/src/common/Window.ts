import { BaseObject } from './BaseObject';
import { WindowConfig } from './WindowConfig';
import { ViewConfig } from './ViewConfig';
import { View } from './View';
export class Window extends BaseObject {
  view: View;
  viewOverlay: View[] = [];
  protected static windows: Window[] = [];
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
    let result = this.__storeWindow(obj.winId, obj.viewId);
    return result;
  }
  /**
   * 根据Id获取Window对象，静态方法
   * @param id
   * @returns
   */
  static getWindowById(id: number): Window | any {
    let result = Window.windows.find((v) => v.id === id);
    return result;
  }
  /**
   * 获取所有窗口，静态方法
   * @returns
   */
  static getAllWindow(): Window[] {
    return Window.windows;
  }
  private static __storeWindow(winId, viewId): Window | any {
    let win = this.getWindowById(winId);
    if (win) return null;
    let result = new Window(winId);
    result.view = View.__createView(viewId);
    this.windows.push(result);
    return result;
  }
  /**
   * 这是框架用的方法，不要尝试在业务代码中使用此方法
   * 如果渲染进程创建了窗口，Node进程需要持有这个窗口
   * 如果Node进程创建了窗口，渲染进程需要持有这个窗口
   */
  static __internalListen() {
    //窗口创建成功
    globalThis.cefMessageChannel.on('windowCreated', (param) => {
      this.__storeWindow(param.winId, param.viewId);
    });
    //子view创建成功
    globalThis.cefMessageChannel.on('viewOverlayCreated', (param) => {
      let win = this.getWindowById(param.winId) as Window;
      if (!win) {
        throw new Error('win not found');
      }
      let index = win.viewOverlay.findIndex((v) => v.id === param.viewId);
      if (index > -1) {
        return;
      }
      let result = View.__createView(param.viewId);
      win.viewOverlay.push(result);
    });
    //窗口关闭
    globalThis.cefMessageChannel.on('windowRemoved', (param) => {
      let index = this.windows.findIndex((v) => v.id === param.winId);
      if (index < 0) return;
      this.windows.splice(index, 1);
    });
    //子View移除
    globalThis.cefMessageChannel.on('viewRemoved', (param) => {
      let win = this.getWindowById(param.winId) as Window;
      if (!win) {
        throw new Error('win not found');
      }
      let index = win.viewOverlay.findIndex((v) => v.id === param.viewId);
      if (index < 0) {
        return;
      }
      win.viewOverlay.splice(index);
    });
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
