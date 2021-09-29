import { Util } from '../Util'
import { Base } from './Base'

export class Shell extends Base {
  openExternal(config: { target; workingDir }) {
    let msgName = this.getFirstArgument(this.openExternal)
    Util.callHorse(msgName, JSON.stringify(config))
  }
}
