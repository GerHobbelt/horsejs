import { eventer } from '../eventer'
import { Util } from '../Util'
declare let __callHorseFunc: (msgName: string, ...otherParams) => {}
export class Base {
  className = 'Base'
  protected createMsgName(method: Function) {
    return `${this.className}_${method.name}_${Util.randomNum()}`
  }
  protected callHorseNative(msgName: string, ...otherParams) {
    __callHorseFunc(msgName, ...otherParams)
  }
  protected callHorse(method: Function, config: Object) {
    return new Promise((resolve, reject) => {
      let msgName = this.createMsgName(method)
      eventer.addOnceEventListener(msgName, (result) => resolve(result))
      this.callHorseNative(msgName, JSON.stringify(config))
    })
  }
}
