import http from 'http';
import serve from 'koa-static';
import path from 'path';
import Koa from 'koa';
import { WebSocketServer, WebSocket } from 'ws';
import { AddressInfo } from 'net';
import { config } from './config';
import fs from 'fs';
import EventEmitter from 'eventemitter3';
import { spawn } from 'child_process';
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
  private listenCefEvent() {
    globalThis.cefMessageChannel.on('windowCreated', (param) => {
      this.emit('windowCreated', param);
    });
    globalThis.cefMessageChannel.on('viewOverlayCreated', (param) => {
      this.emit('viewOverlayCreated', param);
    });
  }

  private listenClientMessage(ws: WebSocket) {
    ws.addListener('upgrade', (e) => {
      console.log('node backend upgrade', e);
    });
    ws.addListener('message', (message, isBinary) => {
      let messageStr = message.toString('utf8');
      console.log('message', messageStr);
      let msg = JSON.parse(messageStr);
      this.emit(msg['__wsMsgName'].toString(), msg);
    });
    ws.addListener('error', (e) => {
      console.log('node backend error', e);
    });
    console.log('node backend onmessage');
  }

  /**
   * 当有客户端连接到websocket服务会触发指定的事件
   * 当Browser进程连接到websocket服务后触发browserReady事件（这个事件只会被触发一次）
   * 当渲染进程连接到websocket服务后触发clientReady事件（这个事件可能会被触发多次）
   * @param ws
   * @param req
   */
  private websocketConnected(ws: WebSocket, req) {
    if (req.url?.endsWith('browser')) {
      globalThis.cefMessageChannel.init(ws);
      this.emit('browserReady', ws, req);
      this.listenCefEvent();
    } else {
      this.emit('clientReady', ws, req);
      this.listenClientMessage(ws);
    }
  }
  /**
   * 初始化http服务和websocket服务
   * 当http服务和websocket服务初始化成功后会触发，serviceReady事件
   * 接着启动CEF进程
   * @param app
   */
  private initHttpAndWebSocketService(app: any) {
    let server = http.createServer(app.callback());
    let wss = new WebSocketServer({ server });
    wss.on('connection', (ws, req) => this.websocketConnected(ws, req));
    server.listen(Number(config.httpAndWebSocketServicePort), 'localhost');
    server.addListener('listening', () => {
      let port = (server.address() as AddressInfo).port;
      console.log(`backend server start:[http://][ws://]localhost:${port}`);
      this.emit('serviceReady', app);
      this.startBrowserProcess(port);
    });
  }
  private startBrowserProcess(port: number) {
    //todo 生产环境不需要拷贝
    let configPath = path.join(__dirname, '../config.json');
    fs.writeFileSync(configPath, JSON.stringify(this.config));
    // let childProcess = spawn(config.browser, [], { detached: true, cwd: path.dirname(config.browser) });
  }
  handle(name: string, callBack: any) {
    this.on(name, (msg) => {
      let result = callBack(msg);
    });
  }
  handleOnce(name: string, callBack: any) {
    this.once(name, callBack);
  }
  removeOneHandle(name: string, callBack: any) {
    this.removeListener(name, callBack);
  }
  removeAllHandle(name: string) {
    this.removeAllListeners(name);
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
