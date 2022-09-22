import { BaseView } from '../common/BaseView';
import { ViewConfig } from '../common/ViewConfig';
export class View extends BaseView {
  /**
   * 获取当前View的MainFrame的Url
   * 刚刚创建窗口后，马上取URL得到的是空值
   * @returns
   */
  async getUrl(): Promise<string> {
    let msg = super.prepareMsg(this.getUrl.name, {});
    let result = await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
    return result.url;
  }

  static __createView(id: number) {
    return new View(id);
  }
}
