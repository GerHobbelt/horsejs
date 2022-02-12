import { eventer } from '../eventer'
import { Base } from './Base'

export class Menu extends Base {
  async popup(config: { data: [{}]; position?: { x: number; y: number }; click: (index) => {} }) {
    if (!config.position) {
      config.position = { x: -1, y: -1 }
    }
    return new Promise((resolve, reject) => {
      let msgName = this.createMsgName(this.popup)
      eventer.addOnceEventListener(msgName, (result) => {
        resolve({ success: true })
      })
      eventer.addOnceEventListener(msgName + '_event', (result) => {
        config.click(result.index)
      })
      this.callHorseNative(msgName, JSON.stringify(config))
    })
  }
}
