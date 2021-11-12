import { horse } from '../../src/main'
export class Window {
  static className = 'Window'
  async windowSizeChange() {
    let result = await horse.window.resize({ width: 800, height: 600 })
    console.log(result)
  }
  async hideShowWindow() {
    let result = await horse.window.hide()
    setTimeout(() => {
      horse.window.show()
    }, 3000)
    console.log(result)
  }
  async maximizeWindow() {
    let result = await horse.window.maximize()
    console.log(result)
  }
  async restoreWindow() {
    let result = await horse.window.restore()
    console.log(result)
  }
  async minimizeWindow() {
    let result = await horse.window.minimize()
    console.log(result)
  }
  async closeWindow() {
    let result = await horse.window.close()
    console.log(result)
  }
  async centerWindow() {
    let result = await horse.window.center()
    console.log(result)
  }
  async openDevTool() {
    let result = await horse.window.openDevTool()
    console.log(result)
  }
  async closeDevTool() {
    let result = await horse.window.closeDevTool()
    console.log(result)
  }
}
