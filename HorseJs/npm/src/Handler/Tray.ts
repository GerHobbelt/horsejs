import { eventer } from '../eventer'
import { Base } from './Base'
type menuDataType = { name: string; id?: number; subMenu?: menuDataType[] }
export class Tray extends Base {
  className = 'Tray'
  isInit = false
  async create(config: { iconPath: string; tip?: string; menu: menuDataType[]; menuClick: (index) => void; [propName: string]: any }) {
    if (this.isInit) {
      throw new Error('已经创建了一个托盘图标')
      return
    }
    return new Promise((resolve, reject) => {
      let msgName = `${this.className}_create`
      eventer.addOnceEventListener(msgName, (result) => {
        resolve({ success: true })
      })
      eventer.removeEventListener(msgName + '_tray')
      eventer.removeEventListener(msgName + '_menu')
      eventer.addEventListener(msgName + '_tray', (result) => {
        if (!config[result.clickType]) return
        config[result.clickType]()
      })
      eventer.addEventListener(msgName + '_menu', (result) => {
        config.menuClick(result.index)
      })
      this.callHorseNative(msgName, JSON.stringify(config))
      this.isInit = true
    })
  }
  async destroy() {
    return new Promise((resolve, reject) => {
      let msgName = `${this.className}_destroy`
      eventer.removeEventListener(msgName + '_tray')
      eventer.removeEventListener(msgName + '_menu')
      this.callHorseNative(msgName, `{}`)
      this.isInit = false
    })
  }
  async resetIcon(config: { iconPath: string; tip: string }) {
    return this.callHorse(this.resetIcon, config)
  }
}
