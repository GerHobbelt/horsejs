import { eventer } from './eventer'
import { Util } from './util'
declare let __callHorseFunc: (msgName: string, ...otherParams: any[]) => {}
export class Base {
  className = 'Base'
  protected createMsgName(method: Function) {
    return `${this.className}_${method.name}_${Util.randomNum()}`
  }
  protected callHorseNative(msgName: string, ...otherParams: any[]) {
    __callHorseFunc(msgName, ...otherParams)
  }
  protected callHorse(method: Function, config: Object): Promise<{ success: boolean; data: any; error?: string }> {
    return new Promise((resolve, reject) => {
      let msgName = this.createMsgName(method)
      eventer.addOnceEventListener(msgName, (result: any) => resolve(result))
      this.callHorseNative(msgName, JSON.stringify(config))
    })
  }
}
