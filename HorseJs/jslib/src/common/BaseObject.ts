import EventEmitter from 'events';

export class BaseObject extends EventEmitter {
  public id: number;
  addListener(eventName: string, listener: (...args: any[]) => void): this {
    globalThis.cefMessageChannel.addListener(`${eventName}_${this.id}`, listener);
    return this;
  }
  removeListener(eventName: string, listener: (...args: any[]) => void): this {
    globalThis.cefMessageChannel.removeListener(`${eventName}_${this.id}`, listener);
    return this;
  }
  once(eventName: string, listener: (...args: any[]) => void): this {
    globalThis.cefMessageChannel.once(`${eventName}_${this.id}`, listener);
    return this;
  }
  on(eventName: string, listener: (...args: any[]) => void): this {
    globalThis.cefMessageChannel.on(`${eventName}_${this.id}`, listener);
    return this;
  }
  off(eventName: string, listener: (...args: any[]) => void): this {
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
  prependListener(eventName: string, listener: (...args: any[]) => void): this {
    globalThis.cefMessageChannel.prependListener(`${eventName}_${this.id}`, listener);
    return this;
  }
  prependOnceListener(eventName: string, listener: (...args: any[]) => void): this {
    globalThis.cefMessageChannel.prependOnceListener(`${eventName}_${this.id}`, listener);
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
