import { Util } from '../Util'
import { eventer } from '../eventer'
import { DialogConfig } from './DialogConfig'
import { Base } from './Base'
export class Dialog extends Base {
  openFile(config: DialogConfig) {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.openFile)
      eventer.addEventListener(msgName, (result) => resolve(result))
      Util.callHorse(msgName, JSON.stringify(config))
    })
  }
  openFolder(config: DialogConfig) {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.openFolder)
      eventer.addEventListener(msgName, (result) => {
        resolve(result)
      })
      Util.callHorse(msgName, JSON.stringify(config))
    })
  }
}
