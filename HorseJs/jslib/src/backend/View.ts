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
   * 显示alert对话框
   * 对于Node进程来说这个方法时非阻塞的
   * 但对于Browser进程来说，却是阻塞的
   * @param text
   */
  async alert(text: string) {
    let msg = super.prepareMsg(this.alert.name, { text });
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }
  /**
   * 显示confirm对话框
   * @param text
   */
  async confirm(text: string) {
    let msg = super.prepareMsg(this.confirm.name, { text });
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }
  static __createView(id: number) {
    return new View(id);
  }
}
