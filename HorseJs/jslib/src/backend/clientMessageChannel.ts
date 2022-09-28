import EventEmitter from 'eventemitter3';
import { WebSocket } from 'ws';
import { Util } from '../common/Util';
class ClientMessageChannel extends EventEmitter {
  private wss: WebSocket[] = [];
  init(ws: WebSocket, clientId: string) {
    ws['__id'] = this.wss.length;
    this.wss.push(ws);
    this.listenClientMessage(ws);
  }
  private listenClientMessage(ws: WebSocket) {
    ws.addListener('upgrade', (e) => {
      console.log('node backend upgrade', e);
    });
    ws.addListener('message', (message, isBinary) => {
      let messageStr = message.toString('utf8');
      let msg = JSON.parse(messageStr);
      msg['__wsId'] = ws['__id'];
      this.emit(msg['__wsMsgName'], msg);
    });
    ws.addListener('error', (e) => {
      console.log('node backend error', e);
    });
  }
  sendMsgToClient(msg: any) {
    //todo 没找到
    let ws = this.wss.find((v) => v['__id'] === msg['__wsId']);
    delete msg['__wsId'];
    let msgStr = JSON.stringify(msg);
    ws?.send(msgStr);
  }
}
globalThis.clientMessageChannel = new ClientMessageChannel();
