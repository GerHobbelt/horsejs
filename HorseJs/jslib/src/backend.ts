import { browserMessageChannel } from './backend/messageChannel/browserMessageChannel'
import { WebSocket } from 'ws'
import { IncomingMessage } from 'http'
import http from 'http'
import serve from 'koa-static'
import path from 'path'
import Koa from 'koa'
import { WebSocketServer } from 'ws'
import { AddressInfo } from 'net'
import { config } from './backend/config'
import { Window } from './backend/controller/window'
import { spawn } from 'child_process'
import fs from 'fs'
class Horse {
  /**
   * 当静态文件服务，koa服务，websocket服务全部准备妥当之后执行此方法
   */
  onServiceReady?: (app: Koa) => void
  /**
   * 当Browser进程连接到websocket服务后执行此方法
   */
  onBrowserReady?: (webSocketClient: WebSocket, reqest: IncomingMessage) => void
  /**
   * 当渲染进程连接到websocket服务后执行此方法
   * 此方法可能会被执行多次
   */
  onClientReady?: (webSocketClient: WebSocket, reqest: IncomingMessage) => void

  config = config
  window: Window = new Window()
  private initStaticService(app: any) {
    let staticPath = path.join(__dirname, '../client')
    app.use(
      serve(staticPath, {
        maxage: 604800000, //7天
        gzip: false,
        brotli: false,
      })
    )
  }
  private initHttpAndWebSocketService(app: any) {
    let server = http.createServer(app.callback())
    let wss = new WebSocketServer({
      server,
      perMessageDeflate: { threshold: 1024 },
    })

    wss.on('connection', (ws, req) => {
      if (req.url?.endsWith('browser')) {
        browserMessageChannel.init(ws)
        if (this.onBrowserReady) this.onBrowserReady(ws, req)
      } else {
        if (this.onClientReady) this.onClientReady(ws, req)
      }
    })

    server.listen(Number(config.httpAndWebSocketServicePort), 'localhost')
    server.addListener('listening', () => {
      let address = server.address() as AddressInfo
      console.log('server start', address.port)
      if (this.onServiceReady) this.onServiceReady(app)
      this.startBrowserProcess(address.port)
    })
  }
  private startBrowserProcess(port: number) {
    let configPath = path.join(__dirname, '../config.json')
    fs.writeFileSync(configPath, JSON.stringify(this.config))
    //todo debug
    // let devenvPath = `C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\IDE\\devenv.exe`
    // let childProcess = spawn(devenvPath, [`/nosplash`, `/runexit`, `D:\\project\\horsejs\\HorseJs.sln`, `servicePort=` + port], { detached: true })
  }
  /**
   * 启动horse
   */
  init(config) {
    Object.assign(this.config, config)
    const app = new Koa()
    this.initStaticService(app)
    this.initHttpAndWebSocketService(app)
  }
}
export let horse = new Horse()
export { WindowConfig } from './backend/controller/windowConfig/WindowConfig'
export { WindowMultiViewsConfig } from './backend/controller/windowConfig/WindowMultiViewsConfig'
export { WindowOverlayViewConfig, WindowOverlayDockMode } from './backend/controller/windowConfig/WindowOverlayViewConfig'
