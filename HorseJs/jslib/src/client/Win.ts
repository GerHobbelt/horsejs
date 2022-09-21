import { View } from './View';
import { BaseWindow } from '../common/BaseWindow';

export class Win extends BaseWindow {
  private isMaximized = false;
  private static currentWindow: Win;
  /**
   * 获取当前窗口
   * todo 如果是在一个overlayView中，获取到这个窗口对象是正确的，但view对象是错的
   * 因为view对象指向的是overlayView而不是窗口的主View
   * @returns
   */
  static getCurrentWindow(): Win {
    if (this.currentWindow) return this.currentWindow;
    this.currentWindow = new Win(globalThis.__winId);
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
