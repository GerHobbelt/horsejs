import EventEmitter from 'eventemitter3';
class CEFMessageChannel extends EventEmitter {
  private nativeCallBack(message: any) {
    let msg = JSON.parse(message);
    this.emit(msg['__msgId'], msg);
  }
  sendMsgToBrowser(msg: any): Promise<any> {
    return new Promise((resolve, reject) => {
      let msgId = Math.random();
      msg['__msgId'] = msgId;
      this.once(msgId.toString(), (obj) => resolve(obj));
      //todo reject
      let msgStr = JSON.stringify(msg);
      //@ts-ignore
      window.nativeCall(msg.__className, msgStr);
    });
  }
  constructor() {
    super();
    //@ts-ignore
    window.nativeCall('__registeNativeCallback', (message) => this.nativeCallBack(message));
  }
}
globalThis.cefMessageChannel = new CEFMessageChannel();
