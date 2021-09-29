import { eventer } from '../eventer'
import { Util } from '../Util'
import { Base } from './Base'

export class Clipboard extends Base {
  getData(config: { dataType: string }) {
    return this.callHorse(this.getData, config)
  }
  setData(config: { dataType: string; data: string | [string] }) {
    return this.callHorse(this.setData, config)
  }
}
