import * as EventEmitter from 'eventemitter3';
class CEFMessageChannel extends EventEmitter {
  sendMessage(message: any, param: any) {
    //@ts-ignore
    window.nativeCall(message, param);
  }
  private nativeCallBack(message: any) {
    let msg = JSON.parse(message);
    this.emit(msg['__msgId'], msg.param);
  }
  constructor() {
    super();
    //@ts-ignore
    window.nativeCall('__registeNativeCallback', (message) => this.nativeCallBack(message));
  }
}
globalThis.cefMessageChannel = new CEFMessageChannel();
