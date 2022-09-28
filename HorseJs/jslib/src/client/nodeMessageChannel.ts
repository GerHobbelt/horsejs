import EventEmitter from 'eventemitter3';
import { Util } from '../common/Util';
class NodeMessageChannel extends EventEmitter {
  private ws: WebSocket;
  sendMsgToNode(msg: any): Promise<any> {
    return new Promise((resolve, reject) => {
      let __msgId = Util.randomNum();
      this.once(__msgId.toString(), (result) => {
        resolve(result);
      });
      msg['__msgId'] = __msgId.toString();
      let msgStr = JSON.stringify(msg);
      this.ws.send(msgStr);
    });
  }
  private initWebSocket() {
    let url = `ws://localhost:${globalThis.__horse.port}/?client=client`;
    this.ws = new WebSocket(url);
    this.ws.onopen = () => {
      console.log('websocket connected', url);
    };
    this.ws.onmessage = (e) => {
      let msgStr = e.data.toString();
      let msg = JSON.parse(msgStr);
      this.emit(msg.__msgId, msg);
      delete msg.__msgId;
    };
    this.ws.onerror = (e) => {
      console.log(e);
    };
    this.ws.onclose = () => {
      //error
      console.log('websocket closed');
    };
  }
  constructor() {
    super();
    this.initWebSocket();
  }
}
globalThis.nodeMessageChannel = new NodeMessageChannel();
