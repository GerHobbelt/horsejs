import EventEmitter from 'eventemitter3';
import { WebSocket } from 'ws';
class CEFMessageChannel extends EventEmitter {
  ws: WebSocket;
  private onWebSocketMessage(message) {
    let msg = JSON.parse(message.toString('utf8'));
    // console.log('eventName', eventName)
    this.emit(msg['__msgId'].toString(), msg);
  }
  sendMessage(message: any) {
    let msgStr = JSON.stringify(message);
    this.ws.send(msgStr);
  }
  init(ws: WebSocket) {
    this.ws = ws;
    this.ws.on('message', (message) => this.onWebSocketMessage(message));
  }
}
globalThis.cefMessageChannel = new CEFMessageChannel();
