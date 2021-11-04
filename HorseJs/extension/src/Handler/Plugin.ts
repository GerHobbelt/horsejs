import { Base } from './Base'

export class Plugin extends Base {
  className = 'Plugin'
  load(config: { name: string; async?: false; paramObject: {} }) {
    return this.callHorse(this.load, config)
  }
  excute(config: { name: string; async?: false; paramObject: {} }) {
    return this.callHorse(this.excute, config)
  }
  unload(config: { name: string; async?: false; paramObject: {} }) {
    return this.callHorse(this.unload, config)
  }
}
