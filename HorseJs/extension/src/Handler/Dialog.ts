import { Util } from '../Util'
import { Eventer } from './Eventer'
export class Dialog {
  private getFirstArgument(method: Function) {
    return `${Dialog.name}_${method.name}_${Util.randomNum()}`
  }
  openFile({ title, defaultFilePath, filters, lastFilterIndex }) {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.openFile)
      console.log(msgName)
      Eventer.addEventListener(msgName, (result) => {
        resolve(result)
      })
      //todo 不要结构，直接传对象
      Util.callHorse(msgName, title, defaultFilePath, filters, lastFilterIndex)
    })
  }
  openFolder({ title, defaultFilePath, filters, lastFilterIndex, cb }) {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.openFolder)
      Eventer.addEventListener(msgName, (result) => {
        resolve(result)
      })
      //todo 不要结构，直接传对象
      Util.callHorse(msgName, title, defaultFilePath, filters, lastFilterIndex)
    })
  }
}
