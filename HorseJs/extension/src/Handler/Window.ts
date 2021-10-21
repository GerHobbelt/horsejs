import { Util } from '../Util'
import { eventer } from '../eventer'
import { WindowConfig } from './WindowConfig'
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
  open(config: WindowConfig) {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.open)
      eventer.addEventListener(msgName, (result) => resolve(result))
      Util.callHorse(msgName, JSON.stringify(config))
    })
  }
  addEventListener(eventName: eventType, cb: Function) {
    eventer.addEventListener(`${Window.name}_${eventName}`, cb)
  }
  removeEventListener(eventName: eventType, cb: Function) {
    eventer.removeEventListener(`${Window.name}_${eventName}`, cb)
  }
  getIsMaximized() {
    return window.outerHeight === screen.availHeight && window.outerWidth === screen.availWidth
  }
  maximize() {
    let msgName = this.getFirstArgument(this.maximize)
    Util.callHorse(msgName)
  }
  minimize() {
    let msgName = this.getFirstArgument(this.minimize)
    Util.callHorse(msgName)
  }
  close() {
    let msgName = this.getFirstArgument(this.close)
    Util.callHorse(msgName)
  }
  restore() {
    let msgName = this.getFirstArgument(this.restore)
    Util.callHorse(msgName)
  }
  hide() {
    let msgName = this.getFirstArgument(this.hide)
    Util.callHorse(msgName)
  }
  show() {
    let msgName = this.getFirstArgument(this.show)
    Util.callHorse(msgName)
  }
  resize(size: { width; height }) {
    let msgName = this.getFirstArgument(this.resize)
    Util.callHorse(msgName, size)
  }
  constructor() {
    this.processMaximizeEvent()
    this.processShowEvent()
  }
}
