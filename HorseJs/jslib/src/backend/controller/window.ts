import { WindowConfig } from './windowConfig/WindowConfig'
import { WindowMultiViewsConfig } from './windowConfig/WindowMultiViewsConfig'
import { browserMessageChannel } from '../messageChannel/browserMessageChannel'
import { WindowOverlayViewConfig } from './windowConfig/WindowOverlayViewConfig'
export class Window {
  createWindow(config: WindowConfig) {
    let msg = {
      className: Window.name,
      actionName: this.createWindow.name,
      params: config,
    }
    browserMessageChannel.sendMessage(msg)
  }
  createWindowMultiView(config: WindowMultiViewsConfig) {
    let msg = {
      className: Window.name,
      actionName: this.createWindowMultiView.name,
      params: config,
    }
    browserMessageChannel.sendMessage(msg)
  }
  createWindowOverlayView(config: WindowOverlayViewConfig) {
    let msg = {
      className: Window.name,
      actionName: this.createWindowOverlayView.name,
      params: config,
    }
    browserMessageChannel.sendMessage(msg)
  }
}
