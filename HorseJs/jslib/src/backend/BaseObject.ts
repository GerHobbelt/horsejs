import { browserMessageChannel } from './browserMessageChannel'
import EventEmitter from 'events'

export class BaseObject extends EventEmitter {
  public id: number
  addListener(eventName: string, listener: (...args: any[]) => void): this {
    browserMessageChannel.addListener(`${eventName}_${this.id}`, listener)
    return this
  }
  removeListener(eventName: string, listener: (...args: any[]) => void): this {
    browserMessageChannel.removeListener(`${eventName}_${this.id}`, listener)
    return this
  }
  once(eventName: string, listener: (...args: any[]) => void): this {
    browserMessageChannel.once(`${eventName}_${this.id}`, listener)
    return this
  }
  on(eventName: string, listener: (...args: any[]) => void): this {
    browserMessageChannel.on(`${eventName}_${this.id}`, listener)
    return this
  }
  off(eventName: string, listener: (...args: any[]) => void): this {
    browserMessageChannel.off(`${eventName}_${this.id}`, listener)
    return this
  }
  removeAllListeners(event?: string | undefined): this {
    if (event) {
      browserMessageChannel.removeAllListeners(`${event}_${this.id}`)
    }
    super.removeAllListeners(event)
    return this
  }
  prependListener(eventName: string, listener: (...args: any[]) => void): this {
    browserMessageChannel.prependListener(`${eventName}_${this.id}`, listener)
    return this
  }
  prependOnceListener(eventName: string, listener: (...args: any[]) => void): this {
    browserMessageChannel.prependOnceListener(`${eventName}_${this.id}`, listener)
    return this
  }
  static sendMsgToBrowser(msg: any) {
    return new Promise((resolve, reject) => {
      let msgId = Math.random()
      msg['__msgId'] = msgId
      browserMessageChannel.once(msgId.toString(), (obj) => resolve(obj))
      //todo reject
      browserMessageChannel.sendMessage(msg)
    })
  }
  constructor(id: number) {
    super()
    this.id = id
  }
}
