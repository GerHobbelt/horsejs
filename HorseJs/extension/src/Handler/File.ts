import { eventer } from '../eventer'
import { Util } from '../Util'

export class File {
  private getFirstArgument(method: Function) {
    return `${File.name}_${method.name}_${Util.randomNum()}`
  }
  readDir(config: { folderPath: string }) {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.readDir)
      eventer.addEventListener(msgName, (result) => resolve(result))
      Util.callHorse(msgName, JSON.stringify(config))
    })
  }
  stat(config: { path: string }) {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.stat)
      eventer.addEventListener(msgName, (result) => resolve(result))
      Util.callHorse(msgName, JSON.stringify(config))
    })
  }
}
