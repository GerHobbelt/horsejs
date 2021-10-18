import { Util } from '../Util'
import { eventer } from '../eventer'
import { DialogConfig } from './DialogConfig'
export class Dialog {
  private getFirstArgument(method: Function) {
    return `${Dialog.name}_${method.name}_${Util.randomNum()}`
  }
  openFile(config: DialogConfig) {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.openFile)
      eventer.addEventListener(msgName, (result) => resolve(result))
      //todo 不要结构，直接传对象
      Util.callHorse(msgName, JSON.stringify(config))
    })
  }
  openFolder(config: DialogConfig) {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.openFolder)
      eventer.addEventListener(msgName, (result) => {
        resolve(result)
      })
      //todo 不要结构，直接传对象
      Util.callHorse(msgName, JSON.stringify(config))
    })
  }
}
