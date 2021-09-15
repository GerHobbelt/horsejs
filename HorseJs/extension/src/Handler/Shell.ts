import { Util } from '../Util'

export class Shell {
  private getFirstArgument(method: Function) {
    return `${Shell.name}_${method.name}_${Util.randomNum()}`
  }
  openExternal(config: { target; workingDir }) {
    let msgName = this.getFirstArgument(this.openExternal)
    Util.callHorse(msgName, JSON.stringify(config))
  }
}
