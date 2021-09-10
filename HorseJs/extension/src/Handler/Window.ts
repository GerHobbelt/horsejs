import { Util } from '../Util'

export class Window {
  private getFirstArgument(method: Function) {
    // @ts-ignore
    return `${Window.name}_${method.name}_${Util.randomNum()}`
  }
  maximize() {
    let arg = this.getFirstArgument(this.maximize)
    __horseFunc(arg)
  }
  minimize() {
    let arg = this.getFirstArgument(this.minimize)
    __horseFunc(arg)
  }
  close() {
    let arg = this.getFirstArgument(this.close)
    __horseFunc(arg)
  }
  restore() {
    let arg = this.getFirstArgument(this.restore)
    __horseFunc(arg)
  }
  hide() {
    let arg = this.getFirstArgument(this.hide)
    __horseFunc(arg)
  }
  show() {
    let arg = this.getFirstArgument(this.show)
    __horseFunc(arg)
  }
  resize(width, height) {
    let arg = this.getFirstArgument(this.resize)
    __horseFunc(arg)
  }
}
