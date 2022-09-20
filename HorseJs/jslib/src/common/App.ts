import EventEmitter from 'eventemitter3';
class App extends EventEmitter {
  private prepareMsg(actionName: string, msg: any) {
    let result = {
      __className: 'App',
      __actionName: actionName,
    };
    Object.assign(result, msg);
    return result;
  }
  async getVersionInfo() {
    let msg = this.prepareMsg(this.getVersionInfo.name, {});
    let result = await globalThis.cefMessageChannel.sendMsgToBrowser(msg);
    return result;
  }
}
export let app = new App();
