import { Util } from '../Util'
import { eventer } from '../eventer'
import { WindowConfig } from './WindowConfig'
import { Base } from './Base'
declare type eventType = 'maximize' | 'unMaximize' | 'show' | 'hide'
export class Window extends Base {
  className = 'Window'
  isMaximized = false
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
    return this.callHorse(this.open, config)
  }
  addEventListener(eventName: eventType, cb: Function) {
    eventer.addEventListener(`${Window.name}_${eventName}`, cb)
  }
  removeEventListener(eventName: eventType, cb: Function) {
    eventer.removeEventListener(`${Window.name}_${eventName}`, cb)
  }
  getIsMaximized() {
    let hSpan = window.outerHeight - screen.availHeight
    let wSpan = window.outerWidth - screen.availWidth
    return Math.abs(hSpan) < 2 && Math.abs(wSpan) < 2
  }
  maximize() {
    return this.callHorse(this.maximize, {})
  }
  minimize() {
    return this.callHorse(this.minimize, {})
  }
  close() {
    return this.callHorse(this.close, {})
  }
  restore() {
    return this.callHorse(this.restore, {})
  }
  hide() {
    return this.callHorse(this.hide, {})
  }
  show() {
    return this.callHorse(this.show, {})
  }
  resize(config: { width; height }) {
    return this.callHorse(this.resize, config)
  }
  center() {
    return this.callHorse(this.center, {})
  }
  constructor() {
    super()
    this.processMaximizeEvent()
    this.processShowEvent()
  }
}
