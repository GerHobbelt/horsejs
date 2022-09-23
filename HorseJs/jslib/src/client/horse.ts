import EventEmitter from 'eventemitter3';
class Horse {
  onWebSocketMessage(msg: string) {
    console.log(msg);
  }
  init() {
    let url = `ws://localhost:${globalThis.__horse.port}/?client=client`;
    let ws = new WebSocket(url);
    ws.onopen = () => {
      console.log('websocket connected', url);
    };
    ws.onmessage = (e) => this.onWebSocketMessage(e.data.toString());
    ws.onclose = () => {
      //error
      console.log('websocket closed');
    };
  }
  constructor() {
    this.init();
  }
}
export let horse = new Horse();
