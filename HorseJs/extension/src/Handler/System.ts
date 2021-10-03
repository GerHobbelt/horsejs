import { Base } from './Base'

export class System extends Base {
  setAutoStart(config: { setOrRemove: 'set' | 'remove' }) {
    return this.callHorse(this.setAutoStart, config)
  }
}
