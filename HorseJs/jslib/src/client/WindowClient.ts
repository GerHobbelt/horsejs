import { Window } from '../common/Window';
import { View } from '../common/View';
import { BaseObject } from '../common/BaseObject';
export class WindowClient extends Window {
  /**
   * 获取当前窗口
   * @returns
   */
  static async getCurrentWindow(): Promise<Window | any> {
    // winId,viewId,viewOverlay
    // 得把这些东西都初始化了
    let msg = {
      className: 'Window',
      actionName: this.getCurrentWindow.name,
    };
    let obj: any = await BaseObject.sendMsgToBrowser(msg);
    let result = new Window(obj.id);
    result.view = View.__createView(0);
    super.windows.push(result);
    return result;
  }
}
