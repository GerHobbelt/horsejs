import { eventer } from '../eventer'
import { Base } from './Base'

export class System extends Base {
  autoStart(config: { setOrRemove: 'set' | 'remove' }) {
    return this.callHorse(this.autoStart, config)
  }
  protocolClient(config: { setOrRemove: 'set' | 'remove' }) {
    return this.callHorse(this.protocolClient, config)
  }
  notify(config: { title: string; body: string; click: Function; dismiss: Function }) {
    return new Promise((resolve, reject) => {
      let msgName = this.createMsgName(this.notify)
      eventer.addOnceEventListener(msgName, (result) => {
        config[result.type]()
      })
      this.callHorseNative(msgName, JSON.stringify(config))
      resolve({ success: true })
    })
  }
}
