import { Base } from './Base'

export class Db extends Base {
  className = 'Db'
  open() {
    return this.callHorse(this.open, {})
  }
  close() {
    return this.callHorse(this.close, {})
  }
  excute() {
    return this.callHorse(this.excute, {})
  }
}
