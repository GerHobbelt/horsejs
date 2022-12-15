import { View } from './View';
import { BaseWindow } from '../common/BaseWindow';
import { WindowConfig } from '../common/WindowConfig';
export class Win extends BaseWindow {
  private isMaximized = false;
  private static currentWindow: Win;
  view: View;
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
    let result = new Win(obj.winId);
    result.view = View.__createView(obj.viewId);
    return result;
  }
  /**
   * 获取当前窗口
   * todo 如果是在一个overlayView中，获取到这个窗口对象是正确的，但view对象是错的
   * 因为view对象指向的是overlayView而不是窗口的主View
   * @returns
   */
  static getCurrentWindow(): Win {
    if (this.currentWindow) return this.currentWindow;
    this.currentWindow = new Win(globalThis.__horse.winId);
    this.currentWindow.view = View.getMainView();
    return this.currentWindow;
  }
  /**
   * 当前窗口是否处于最大化状态
   * @returns
   */
  getIsMaximized() {
    let hSpan = window.outerHeight - screen.availHeight;
    let wSpan = window.outerWidth - screen.availWidth;
    return Math.abs(hSpan) < 2 && Math.abs(wSpan) < 2;
  }

  private visibilityChange() {
    document.addEventListener('visibilitychange', () => {
      if (document.hidden) this.emit('hidden');
      else this.emit('shown');
    });
  }

  private maximizeChange() {
    let sizeChangeProcessor = () => {
      let curState = this.getIsMaximized();
      let oldState = this.isMaximized;
      this.isMaximized = curState;
      if (oldState && !curState) this.emit(`unMaximized`);
      else if (!oldState && curState) this.emit(`maximized`);
    };
    window.addEventListener('resize', sizeChangeProcessor);
  }

  protected constructor(id: number) {
    super(id);
    this.visibilityChange();
    this.maximizeChange();
  }
}
