import EventEmitter from 'eventemitter3';
import { Util } from '../common/Util';
class Horse extends EventEmitter {
  private ws: WebSocket;
  onWebSocketMessage(msg: string) {
    console.log(msg);
  }
  init() {
    let url = `ws://localhost:${globalThis.__horse.port}/?client=client`;
    this.ws = new WebSocket(url);
    this.ws.onopen = () => {
      console.log('websocket connected', url);
    };
    this.ws.onmessage = (e) => {
      let msgStr = e.data.toString();
      let msg = JSON.parse(msgStr);
      this.emit(msg.__msgId, msg);
    };
    this.ws.onerror = (e) => {
      console.log(e);
    };
    this.ws.onclose = () => {
      //error
      console.log('websocket closed');
    };
  }
  invoke(name, param): Promise<any> {
    return new Promise((resolve, reject) => {
      let __msgId = Util.randomNum();
      this.once(__msgId.toString(), (result) => {
        resolve(result);
      });
      let msg = {
        __msgId: __msgId.toString(),
        __wsMsgName: name,
        ...param,
      };
      let msgStr = JSON.stringify(msg);
      console.log(msgStr);
      this.ws.send(msgStr);
    });
  }
  constructor() {
    super();
    this.init();
  }
}
export let horse = new Horse();
