import { BaseWindow } from '../common/BaseWindow';
export class Win extends BaseWindow {
  private isMaximized = false;
  /**
   * 获取当前窗口
   * @returns
   */
  static async getCurrentWindow(): Promise<Win | any> {
    let msg = {
      __className: 'Win',
      __actionName: this.getCurrentWindow.name,
    };
    let obj: any = await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
    let result = new Win(obj.winId);
    return result;
  }

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
