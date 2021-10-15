import { Util } from '../Util'
import { eventer } from '../eventer'
declare type eventType = 'maximize' | 'unMaximize' | 'show' | 'hide'
export class Window {
  isMaximized = false
  private getFirstArgument(method: Function) {
    return `${Window.name}_${method.name}_${Util.randomNum()}`
  }
  private processMaximizeEvent() {
    this.isMaximized = this.getIsMaximized()
    window.addEventListener(
      'resize',
      Util.debounce(() => {
        let curState = this.getIsMaximized()
        let oldState = this.isMaximized
        this.isMaximized = curState
        if (oldState && !curState) eventer.emitEvent(`${Window.name}_unMaximize`)
        else if (!oldState && curState) eventer.emitEvent(`${Window.name}_maximize`)
      })
    )
  }
  private processShowEvent() {
    document.addEventListener('visibilitychange', () => {
      if (document.hidden) eventer.emitEvent(`${Window.name}_hide`)
      else eventer.emitEvent(`${Window.name}_show`)
    })
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
  addEventListener(eventName: eventType, cb: Function) {
    eventer.addEventListener(`${Window.name}_${eventName}`, cb)
  }
  removeEventListener(eventName: eventType, cb: Function) {
    eventer.addEventListener(`${Window.name}_${eventName}`, cb)
  }
  constructor() {
    this.processMaximizeEvent()
    this.processShowEvent()
  }
}
