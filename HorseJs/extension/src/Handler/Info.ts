import { Base } from './Base'

export class Info extends Base {
  className = 'Info'
  getAppInfo() {
    return this.callHorse(this.getAppInfo, {})
  }
  getHorseInfo() {
    return this.callHorse(this.getHorseInfo, {})
  }
  getOSInfo() {
    return this.callHorse(this.getOSInfo, {})
  }
  getHardwareInfo() {
    return this.callHorse(this.getHardwareInfo, {})
  }
}
