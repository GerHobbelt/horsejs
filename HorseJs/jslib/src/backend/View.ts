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
  /**
   * 为窗口添加view
   * @param config
   * @returns
   */
  async addOverlayView(param: ViewConfig): Promise<BaseView> {
    let msg = this.prepareMsg(this.addOverlayView.name, param);
    let obj: any = await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
    let result = View.__createView(obj.id);
    return result;
  }
  static __createView(id: number) {
    return new View(id);
  }
}
