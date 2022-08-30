import { Base } from './Base'

export class Shell extends Base {
  openExternal(config: { target; workingDir }) {
    return this.callHorse(this.openExternal, config)
  }
}
