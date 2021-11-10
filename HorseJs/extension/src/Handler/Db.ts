import { Base } from './Base'
import { eventer } from '../eventer'

export class Db extends Base {
  className = 'Db'
  open() {
    return this.callHorse(this.open, {})
  }
  close() {
    return this.callHorse(this.close, {})
  }
  execute(config: { sql: string }) {
    return this.callHorse(this.execute, config)
  }
}
