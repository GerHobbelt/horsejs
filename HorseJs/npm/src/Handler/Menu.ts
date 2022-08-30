import { eventer } from '../eventer'
import { Base } from './Base'

type menuDataType = { name?: string; id: number; type?: 'text' | 'check' | 'separator'; checked?: boolean; enable: boolean; subMenu?: menuDataType[] }
export class Menu extends Base {
  className = 'Menu'
  async popup(config: { data: menuDataType[]; click: (index: number) => void; position?: { x: number; y: number } }) {
    if (!config.position) {
      config.position = { x: -1, y: -1 }
    }
    return new Promise((resolve, reject) => {
      let msgName = this.createMsgName(this.popup)
      eventer.addOnceEventListener(msgName, (result: any) => {
        resolve({ success: true })
      })
      eventer.addOnceEventListener(msgName + '_event', (result: any) => {
        config.click(result.id)
      })
      this.callHorseNative(msgName, JSON.stringify(config))
    })
  }
}
