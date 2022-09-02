import { BaseObject } from './BaseObject'
export class Window extends BaseObject {
  async openDevTools() {}
  async closeDevTools() {}
  async wasHiden() {}
  async sendKeyEvent() {}
  async sendMouseClickEvent() {}
  async sendMouseMoveEvent() {}
  async sendMouseWheelEvent() {}
  async sendTouchEvent() {}
  private constructor(id: number) {
    super(id)
  }
}
