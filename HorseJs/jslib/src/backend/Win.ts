import { View } from './View';
import { BaseWindow } from '../common/BaseWindow';
import { WindowConfig } from '../common/WindowConfig';
import { ViewConfig } from '../common/ViewConfig';
export class Win extends BaseWindow {
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
   * 为窗口添加view
   * @param config
   * @returns
   */
  async addOverlayView(param: ViewConfig): Promise<View> {
    let msg = super.prepareMsg(this.addOverlayView.name, param);
    let obj: any = await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
    let result = View.__createView(obj.id);
    return result;
  }
}
