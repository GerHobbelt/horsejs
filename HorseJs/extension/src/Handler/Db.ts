import { Base } from './Base'
import { eventer } from '../eventer'

export class Db extends Base {
  className = 'Db'
  open() {
    return this.callHorse(this.open, {})
  }
  close() {
    return this.callHorse(this.close, {})
  }
  execute(config: { sql: string; onData?: (data) => void }) {
    return new Promise((resolve, reject) => {
      let msgName = this.createMsgName(this.execute)
      eventer.addOnceEventListener(msgName, (result) => {
        resolve(result)
      })
      let dataMsgName = msgName + '_data'
      eventer.addOnceEventListener(dataMsgName, (result) => {
        config.onData(result)
        if (!result.success) {
          throw new Error(result.info)
        }
      })
      this.callHorseNative(msgName, JSON.stringify(config))
    })
  }
}
