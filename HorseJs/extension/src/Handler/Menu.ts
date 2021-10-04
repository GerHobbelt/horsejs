import { Base } from './Base'

export class Menu extends Base {
  async popup(config: { data: [any]; position?: { x: number; y: number } }) {
    console.log(window.event)
    await this.callHorse(this.popup, config)
  }
}
