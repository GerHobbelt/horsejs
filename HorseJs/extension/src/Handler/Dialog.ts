import { Util } from '../Util'
import { eventer } from '../eventer'
import { DialogConfig } from './DialogConfig'
import { Base } from './Base'
export class Dialog extends Base {
  openFile(config: DialogConfig) {
    return this.callHorse(this.openFile, config)
  }
  openFolder(config: DialogConfig) {
    return this.callHorse(this.openFolder, config)
  }
}
