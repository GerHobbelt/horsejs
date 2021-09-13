import { Util } from '../Util'
import { Eventer } from './Eventer'

export class Window {
  isMaximized = false
  private getFirstArgument(method: Function) {
    return `${Window.name}_${method.name}_${Util.randomNum()}`
  }
  getIsMaximized() {
    return window.outerHeight === screen.availHeight && window.outerWidth === screen.availWidth
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
  addEventListener(eventName: 'maximize' | 'unMaximize', cb: Function) {
    Eventer.addEventListener(eventName, cb)
  }
  constructor() {
    this.isMaximized = this.getIsMaximized()
    window.addEventListener(
      'resize',
      Util.debounce(() => {
        let curState = this.getIsMaximized()
        let oldState = this.isMaximized
        this.isMaximized = curState
        if (oldState && !curState) Eventer.emitEvent('unMaximize')
        else if (!oldState && curState) Eventer.emitEvent('maximize')
      })
    )
  }
}
