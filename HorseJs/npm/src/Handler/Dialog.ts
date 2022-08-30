import { DialogConfig } from './DialogConfig'
import { Base } from './Base'
export class Dialog extends Base {
  className = 'Dialog'
  openFile(config: DialogConfig) {
    return this.callHorse(this.openFile, config)
  }
  openFolder(config: DialogConfig) {
    return this.callHorse(this.openFolder, config)
  }
}
