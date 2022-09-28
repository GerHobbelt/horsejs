import EventEmitter from 'eventemitter3';
class Horse extends EventEmitter {
  invoke(name, param): Promise<any> {
    let msg = { __wsMsgName: name, ...param };
    return globalThis.nodeMessageChannel.sendMsgToNode(msg);
  }
  constructor() {
    super();
  }
}
export let horse = new Horse();
