import { BaseObject } from './BaseObject'
export class View extends BaseObject {
  async openDevTools() {}
  async closeDevTools() {}
  async wasHiden() {}
  async sendKeyEvent() {}
  async sendMouseClickEvent() {}
  async sendMouseMoveEvent() {}
  async sendMouseWheelEvent() {}
  async sendTouchEvent() {}
  static __createView(id: number) {
    return new View(id)
  }
  private constructor(id: number) {
    super(id)
  }
}
