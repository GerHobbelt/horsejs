import { Base } from './Base'

export class Menu extends Base {
  popup(config: { data: [any]; position?: { x: number; y: number } }) {
    return this.callHorse(this.popup, config)
  }
}
