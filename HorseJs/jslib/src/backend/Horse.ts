import http from 'http';
import serve from 'koa-static';
import path from 'path';
import Koa from 'koa';
import { WebSocketServer } from 'ws';
import { AddressInfo } from 'net';
import { config } from './config';
import fs from 'fs';
import EventEmitter from 'eventemitter3';
class Horse extends EventEmitter {
  config = config;
  private initStaticService(app: any) {
    let staticPath = path.join(__dirname, '../client');
    app.use(
      serve(staticPath, {
        maxage: 604800000, //7天
        gzip: false,
        brotli: false,
      })
    );
  }
  private websocketConnected(ws, req) {
    if (req.url?.endsWith('browser')) {
      globalThis.cefMessageChannel.init(ws);
      /**
       * 当Browser进程连接到websocket服务后执行此方法
       */
      this.emit('browserReady', ws, req);
      globalThis.cefMessageChannel.on('windowCreated', (param) => {
        this.emit('windowCreated', param);
      });
      globalThis.cefMessageChannel.on('viewOverlayCreated', (param) => {
        this.emit('viewOverlayCreated', param);
      });
      //todo
      // globalThis.cefMessageChannel.on('viewOverlayCreated', (param) => {
      //   this.emit('viewOverlayCreated', param);
      // });
      // globalThis.cefMessageChannel.on('viewOverlayCreated', (param) => {
      //   this.emit('viewOverlayCreated', param);
      // });
    } else {
      /**
       * 当渲染进程连接到websocket服务后执行此方法
       * 此方法可能会被执行多次
       */
      this.emit('clientReady', ws, req);
    }
  }
  private webServiceStarted(port, app) {
    console.log(`backend server start:[http://][ws://]localhost:${port}`);
    /**
     * 当静态文件服务，koa服务，websocket服务全部准备妥当之后执行此方法
     */
    this.emit('serviceReady', app);
    this.startBrowserProcess(port);
  }
  private initHttpAndWebSocketService(app: any) {
    let server = http.createServer(app.callback());
    let wss = new WebSocketServer({
      server,
      perMessageDeflate: { threshold: 1024 },
    });
    wss.on('connection', (ws, req) => this.websocketConnected(ws, req));
    server.listen(Number(config.httpAndWebSocketServicePort), 'localhost');
    server.addListener('listening', () => {
      this.webServiceStarted((server.address() as AddressInfo).port, app);
    });
  }
  private startBrowserProcess(port: number) {
    let configPath = path.join(__dirname, '../config.json');
    fs.writeFileSync(configPath, JSON.stringify(this.config));
    //todo debug
    // let devenvPath = `C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\IDE\\devenv.exe`
    // let childProcess = spawn(devenvPath, [`/nosplash`, `/runexit`, `D:\\project\\horsejs\\HorseJs.sln`, `servicePort=` + port], { detached: true })
  }
  /**
   * 启动horse
   */
  init(config) {
    Object.assign(this.config, config);
    const app = new Koa();
    this.initStaticService(app);
    this.initHttpAndWebSocketService(app);
  }
}
export let horse = new Horse();
