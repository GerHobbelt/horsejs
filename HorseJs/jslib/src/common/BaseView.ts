import EventEmitter from 'eventemitter3';
export class BaseView extends EventEmitter {
  id: number;
  protected prepareMsg(actionName: string, msg: any) {
    let result = {
      __className: 'View',
      __actionName: actionName,
      __viewId: this.id,
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
  private async showFileOrFolderDialog(msg: any) {
    if (!msg.filters || msg.filters.length < 1) {
      msg.filters = ['*'];
    }
    let result = await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
    return result.data;
  }
  async showOpenFolderDialog(param: { title?: string; defaultPath?: string; multiSelection?: boolean; filters?: string[] }): Promise<string> {
    let msg = this.prepareMsg('showFileOrFolderDialog', param) as any;
    msg.type = 'openFolder';
    return await this.showFileOrFolderDialog(msg);
  }
  async showSaveFileDialog(param: { title?: string; defaultPath?: string; multiSelection?: boolean; filters?: string[] }): Promise<string> {
    let msg = this.prepareMsg('showFileOrFolderDialog', param) as any;
    msg.type = 'saveFile';
    return await this.showFileOrFolderDialog(msg);
  }
  async showOpenFileDialog(param: { title?: string; defaultPath?: string; filters?: string[] }): Promise<string[] | string> {
    let msg = this.prepareMsg('showFileOrFolderDialog', param) as any;
    msg.type = 'openFile';
    if (msg.multiSelection === undefined) {
      msg.multiSelection = true;
    }
    return await this.showFileOrFolderDialog(msg);
  }
  async showMessageDialog() {}
  async showErrorDialog() {}
  protected constructor(id: number) {
    super();
    this.id = id;
  }
}
