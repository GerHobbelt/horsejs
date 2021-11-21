import { eventer } from '../eventer'
import { Util } from '../Util'

export class Info {
  private getFirstArgument(method: Function) {
    return `${Info.name}_${method.name}_${Util.randomNum()}`
  }
  horseVersion: string = '0.0.1'
  appVersion: string = '0.0.1'
  osName: string = 'win'
  osArch: string = 'x64'
  getPath(config: { name }) {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.getPath)
      eventer.addEventListener(msgName, (result) => resolve(result))
      Util.callHorse(msgName, JSON.stringify(config))
    })
  }
  getAppInfo() {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.getAppInfo)
      eventer.addEventListener(msgName, (result) => resolve(result))
      Util.callHorse(msgName)
    })
  }
  getHorseInfo() {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.getHorseInfo)
      eventer.addEventListener(msgName, (result) => resolve(result))
      Util.callHorse(msgName)
    })
  }
}
