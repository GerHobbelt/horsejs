import { eventer } from '../eventer'
import { Base } from './Base'

export class System extends Base {
  className = 'System'
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
        resolve({ success: true })
      })
      eventer.addOnceEventListener(msgName + '_event', (result) => {
        config[result.type]()
      })
      this.callHorseNative(msgName, JSON.stringify(config))
    })
  }
  openExternal(config: { target; workingDir }) {
    return this.callHorse(this.openExternal, config)
  }
}