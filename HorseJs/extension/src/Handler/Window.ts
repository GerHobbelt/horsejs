import { Util } from '../Util'

export class Window {
  private getFirstArgument(method: Function) {
    // @ts-ignore
    return `${Window.name}_${method.name}_${Util.randomNum()}`
  }
  maximize() {
    let arg = this.getFirstArgument(this.maximize)
    Util.callHorse(arg)
  }
  minimize() {
    let arg = this.getFirstArgument(this.minimize)
    Util.callHorse(arg)
  }
  close() {
    let arg = this.getFirstArgument(this.close)
    Util.callHorse(arg)
  }
  restore() {
    let arg = this.getFirstArgument(this.restore)
    Util.callHorse(arg)
  }
  hide() {
    let arg = this.getFirstArgument(this.hide)
    Util.callHorse(arg)
  }
  show() {
    let arg = this.getFirstArgument(this.show)
    Util.callHorse(arg)
  }
  resize(width, height) {
    let arg = this.getFirstArgument(this.resize)
    Util.callHorse(arg)
  }
}
