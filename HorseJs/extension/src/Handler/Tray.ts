import { eventer } from '../eventer'
import { Base } from './Base'

export class Tray extends Base {
  className = 'Tray'
  async create(config: { iconPath: string; tip?: string; menu: [{ name: string }]; menuClick: (index) => void; trayClick?: (index) => void }) {
    return new Promise((resolve, reject) => {
      let msgName = `${this.className}_create`
      eventer.addOnceEventListener(msgName, (result) => {
        resolve({ success: true })
      })
      eventer.removeEventListener(msgName + '_tray')
      eventer.removeEventListener(msgName + '_menu')
      eventer.addEventListener(msgName + '_tray', (result) => {
        config.trayClick(result.clickType)
      })
      eventer.addEventListener(msgName + '_menu', (result) => {
        config.menuClick(result.index)
      })
      this.callHorseNative(msgName, JSON.stringify(config))
    })
  }
  async destroy() {
    return new Promise((resolve, reject) => {
      let msgName = `${this.className}_destroy`
      eventer.removeEventListener(msgName + '_tray')
      eventer.removeEventListener(msgName + '_menu')
      this.callHorseNative(msgName, `{}`)
    })
  }
  async resetIcon(config: { iconPath: string }) {
    return this.callHorse(this.resetIcon, config)
  }
}
