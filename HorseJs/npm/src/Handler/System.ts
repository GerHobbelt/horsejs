import { eventer } from '../eventer'
import { Base } from './Base'

export class System extends Base {
  className = 'System'
  autoStart(config: { setOrRemove: 'set' | 'remove' }) {
    return this.callHorse(this.autoStart, config)
  }
  protocolClient(config: { setOrRemove: 'set' | 'remove'; protocolName: string }) {
    return this.callHorse(this.protocolClient, config)
  }
  notify(config: { title: string; body: string; click: Function; dismiss: Function }) {
    return new Promise((resolve, reject) => {
      let msgName = this.createMsgName(this.notify)
      eventer.addOnceEventListener(msgName, (result: any) => {
        resolve({ success: true })
      })
      eventer.addOnceEventListener(msgName + '_event', (result: any) => {
        //@ts-ignore
        config[result.type]()
      })
      this.callHorseNative(msgName, JSON.stringify(config))
    })
  }
  openExternal(config: { target: string; workingDir: string }) {
    return this.callHorse(this.openExternal, config)
  }
}
