import * as EventEmitter from 'eventemitter3';

export class BaseObject extends EventEmitter {
  public id: number;
  addListener(eventName: string | symbol, listener: (...args: any[]) => void): this {
    eventName = eventName as string;
    globalThis.cefMessageChannel.addListener(`${eventName}_${this.id}`, listener);
    return this;
  }
  removeListener(eventName: string | symbol, listener: (...args: any[]) => void): this {
    eventName = eventName as string;
    globalThis.cefMessageChannel.removeListener(`${eventName}_${this.id}`, listener);
    return this;
  }
  once(eventName: string | symbol, listener: (...args: any[]) => void): this {
    eventName = eventName as string;
    globalThis.cefMessageChannel.once(`${eventName}_${this.id}`, listener);
    return this;
  }
  on(eventName: string | symbol, listener: (...args: any[]) => void): this {
    eventName = eventName as string;
    globalThis.cefMessageChannel.on(`${eventName}_${this.id}`, listener);
    return this;
  }
  off(eventName: string | symbol, listener: (...args: any[]) => void): this {
    eventName = eventName as string;
    globalThis.cefMessageChannel.off(`${eventName}_${this.id}`, listener);
    return this;
  }
  removeAllListeners(event?: string | undefined): this {
    if (event) {
      globalThis.cefMessageChannel.removeAllListeners(`${event}_${this.id}`);
    }
    super.removeAllListeners(event);
    return this;
  }
  static sendMsgToBrowser(msg: any): Promise<any> {
    return new Promise((resolve, reject) => {
      let msgId = Math.random();
      msg['__msgId'] = msgId;
      globalThis.cefMessageChannel.once(msgId.toString(), (obj) => resolve(obj));
      //todo reject
      globalThis.cefMessageChannel.sendMessage(msg);
    });
  }
  constructor(id: number) {
    super();
    this.id = id;
  }
}
