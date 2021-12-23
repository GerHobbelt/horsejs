import { eventer } from '../eventer'
import { Util } from '../Util'
import { Base } from './Base'

export class Info extends Base {
  horseVersion: string = '0.0.1'
  appVersion: string = '0.0.1'
  osName: string = 'win'
  osArch: string = 'x64'
  getPath(config: { name }) {
    return this.callHorse(this.getPath, config)
  }
  getAppInfo() {
    return this.callHorse(this.getAppInfo, {})
  }
  getHorseInfo() {
    return this.callHorse(this.getHorseInfo, {})
  }
}
