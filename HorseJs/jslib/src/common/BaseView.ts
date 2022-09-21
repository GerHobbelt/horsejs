import EventEmitter from 'eventemitter3';
export class BaseView extends EventEmitter {
  id: number;
  private prepareMsg(actionName: string, msg: any) {
    let result = {
      __className: 'View',
      __actionName: actionName,
      __winId: this.id,
    };
    Object.assign(result, msg);
    return result;
  }
  async show() {
    let msg = this.prepareMsg('setVisible', { visible: true, viewId: this.id });
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }
  async hide() {
    let msg = this.prepareMsg('setVisible', { visible: false, viewId: this.id });
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }
  async openDevTools() {
    let msg = this.prepareMsg('devTools', { viewId: this.id, option: 'open' });
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }
  async closeDevTools() {
    let msg = this.prepareMsg('devTools', { viewId: this.id, option: 'close' });
    await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
  }
  async wasHiden() {}
  async sendKeyEvent() {}
  async sendMouseClickEvent() {}
  async sendMouseMoveEvent() {}
  async sendMouseWheelEvent() {}
  async sendTouchEvent() {}
  async getUrl() {
    let msg = this.prepareMsg(this.getUrl.name, {});
    let result = await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
    console.log(result);
  }
  async showOpenFileDialog() {}
  async showOpenFolderDialog() {}
  async showSaveFileDialog() {}
  async showMessageDialog() {}
  async showErrorDialog() {}

  static __createView(id: number) {
    return new BaseView(id);
  }
  protected constructor(id: number) {
    super();
    this.id = id;
  }
}
