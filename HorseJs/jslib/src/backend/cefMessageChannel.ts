import EventEmitter from 'eventemitter3';
import { WebSocket } from 'ws';
import { Util } from '../common/Util';
class CEFMessageChannel extends EventEmitter {
  ws: WebSocket;
  private onWebSocketMessage(message) {
    let msg = JSON.parse(message.toString('utf8'));
    this.emit(msg['__msgId'].toString(), msg);
  }
  init(ws: WebSocket) {
    this.ws = ws;
    this.ws.on('message', (message) => this.onWebSocketMessage(message));
  }
  sendMsgToBrowser(msg: any): Promise<any> {
    return new Promise((resolve, reject) => {
      let msgId = Util.randomNum();
      msg['__msgId'] = msgId;
      this.once(msgId.toString(), (obj) => resolve(obj));
      //todo reject
      let msgStr = JSON.stringify(msg);
      this.ws.send(msgStr);
    });
  }
}
globalThis.cefMessageChannel = new CEFMessageChannel();
