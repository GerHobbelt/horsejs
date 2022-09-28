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
      let arr = req.url.split(`=`);
      let clientId = arr[arr.length - 1];
      globalThis.clientMessageChannel.init(ws, clientId);
      this.emit('clientReady', ws, req);
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
  /**
   * 注册handle，处理渲染进程发来的请求。
   * 渲染进程通过horse.invoke()，发起请求。
   * todo 目前还没做removeOneHandle
   * @param name handle名称
   * @param callBack
   */
  handle(name: string, callBack: any) {
    globalThis.clientMessageChannel.on(name, (msg) => {
      let result = callBack(msg);
      result['__wsId'] = msg['__wsId'];
      result['__msgId'] = msg['__msgId'];
      globalThis.clientMessageChannel.sendMsgToClient(result);
    });
  }
  /**
   * 注册一次性handle，处理渲染进程发来的请求。
   * 渲染进程通过horse.invoke()，发起请求，不过只能请求一次
   * @param name handle名称
   * @param callBack
   */
  handleOnce(name: string, callBack: any) {
    globalThis.clientMessageChannel.once(name, (msg) => {
      let result = callBack(msg);
      result['__wsId'] = msg['__wsId'];
      result['__msgId'] = msg['__msgId'];
      globalThis.clientMessageChannel.sendMsgToClient(result);
    });
  }
  /**
   * 移除同名所有的handle
   * @param name handle名称
   */
  removeAllHandle(name: string) {
    globalThis.clientMessageChannel.removeAllListeners(name);
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
