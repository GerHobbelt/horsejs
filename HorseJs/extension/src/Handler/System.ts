import { Base } from './Base'

export class System extends Base {
  autoStart(config: { setOrRemove: 'set' | 'remove' }) {
    return this.callHorse(this.autoStart, config)
  }
  protocolClient(config: { setOrRemove: 'set' | 'remove' }) {
    return this.callHorse(this.protocolClient, config)
  }
}
