import { BaseWindow } from '../common/BaseWindow';
export class Win extends BaseWindow {
  /**
   * 获取当前窗口
   * @returns
   */
  static async getCurrentWindow(): Promise<Win | any> {
    console.log('123');
    // let msg = {
    //   className: 'Window',
    //   actionName: this.getCurrentWindow.name,
    // };
    // let obj: any = await BaseObject.sendMsgToBrowser(msg);
    // let result = new Win(obj.id);
    // result.view = View.__createView(0);
    // return result;
  }
}
