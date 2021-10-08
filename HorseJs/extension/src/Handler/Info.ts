import { Base } from './Base'

export class Info extends Base {
  getAppInfo() {
    return this.callHorse(this.getAppInfo, {})
  }
  getHorseInfo() {
    return this.callHorse(this.getHorseInfo, {})
  }
}
