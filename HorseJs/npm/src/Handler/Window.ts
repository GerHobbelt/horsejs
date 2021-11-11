import { Util } from '../Util'
import { eventer } from '../eventer'
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
        if (oldState && !curState) eventer.emitEvent(`${this.className}_unMaximize`)
        else if (!oldState && curState) eventer.emitEvent(`${this.className}_maximize`)
      })
    )
  }
  private processShowEvent() {
    document.addEventListener('visibilitychange', () => {
      if (document.hidden) eventer.emitEvent(`${this.className}_hide`)
      else eventer.emitEvent(`${this.className}_show`)
    })
  }
  open(config: { width?: number; height?: number; url: string }) {
    if (!config.width) config.width = 1000
    if (!config.height) config.height = 800
    return this.callHorse(this.open, config)
  }
  addEventListener(eventName: eventType, cb: Function) {
    eventer.addEventListener(`${this.className}_${eventName}`, cb)
  }
  removeEventListener(eventName: eventType, cb: Function) {
    eventer.removeEventListener(`${this.className}_${eventName}`, cb)
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
  openDevTool() {
    return this.callHorse(this.openDevTool, {})
  }
  closeDevTool() {
    return this.callHorse(this.closeDevTool, {})
  }
  constructor() {
    super()
    this.processMaximizeEvent()
    this.processShowEvent()
  }
}
