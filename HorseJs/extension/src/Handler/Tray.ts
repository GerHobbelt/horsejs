import { eventer } from '../eventer'
import { Base } from './Base'

export class Tray extends Base {
  className = 'Tray'
  async create(config: { iconPath: string; menu: [{ name: string }]; menuClick: (index) => {} }) {
    return new Promise((resolve, reject) => {
      let msgName = this.createMsgName(this.create)
      eventer.addOnceEventListener(msgName, (result) => {
        resolve({ success: true })
      })
      eventer.addOnceEventListener(msgName + '_event', (result) => {
        config.menuClick(result.index)
      })
      this.callHorseNative(msgName, JSON.stringify(config))
    })
  }
}
