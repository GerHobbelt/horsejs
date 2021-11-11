import { Base } from './Base'

export class Clipboard extends Base {
  className = 'Clipboard'
  getData(config: { dataType: string }) {
    return this.callHorse(this.getData, config)
  }
  setData(config: { dataType: string; data: string | [string] }) {
    return this.callHorse(this.setData, config)
  }
}
