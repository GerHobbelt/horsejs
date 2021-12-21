import { eventer } from '../eventer'
import { Util } from '../Util'

export class Clipboard {
  private getFirstArgument(method: Function) {
    return `${Clipboard.name}_${method.name}_${Util.randomNum()}`
  }
  getData(config: { dataType: string }) {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.getData)
      eventer.addEventListener(msgName, (result) => resolve(result))
      Util.callHorse(msgName, JSON.stringify(config))
    })
  }
  setData(config: { dataType: string; data: string | [string] }) {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.setData)
      eventer.addEventListener(msgName, (result) => resolve(result))
      Util.callHorse(msgName, JSON.stringify(config))
    })
  }
}
