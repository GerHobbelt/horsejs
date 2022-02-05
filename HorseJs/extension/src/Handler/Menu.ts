import { Base } from './Base'

export class Menu extends Base {
  async popup(config: { data: [any]; position?: { x: number; y: number } }) {
    if (!config.position) {
      config.position = { x: -1, y: -1 }
    }
    await this.callHorse(this.popup, config)
  }
}
