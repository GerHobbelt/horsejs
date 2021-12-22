import { eventer } from '../eventer'
import { Util } from '../Util'
import { Base } from './Base'

export class Clipboard extends Base {
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
