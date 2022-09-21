import EventEmitter from 'eventemitter3';
import { Util } from '../common/Util';
class CEFMessageChannel extends EventEmitter {
  private nativeCallBack(message: any) {
    let msg = JSON.parse(message);
    this.emit(msg['__msgId'], msg);
  }
  sendMsgToBrowser(msg: any): Promise<any> {
    return new Promise((resolve, reject) => {
      let msgId = Util.randomNum();
      msg['__msgId'] = msgId;
      this.once(msgId.toString(), (obj) => resolve(obj));
      //todo reject
      let msgStr = JSON.stringify(msg);
      //@ts-ignore
      window.__nativeCall(msgStr);
    });
  }
  constructor() {
    super();
    //@ts-ignore
    window.__nativeCall('__registeNativeCallback', (message) => this.nativeCallBack(message));
  }
}
globalThis.cefMessageChannel = new CEFMessageChannel();
