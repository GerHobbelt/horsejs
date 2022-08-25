import { messageChannel } from "./backend/messageChannel";
import http from "http";
import serve from "koa-static";
import path from "path";
import Koa from "koa";
import { WebSocketServer } from "ws";
import { AddressInfo } from "net";
class Horse {
  private initStaticService(app: any) {
    let staticPath = path.join(__dirname, "../client");
    app.use(
      serve(staticPath, {
        maxage: 604800000, //7天
        gzip: false,
        brotli: false,
      })
    );
  }
  private initHttpAndWebSocketService(app: any) {
    let cmdPort = process.argv[2];
    let port = cmdPort ? parseInt(cmdPort) : 5916;
    let server = http.createServer(app.callback());
    let wss = new WebSocketServer({
      server,
      perMessageDeflate: { threshold: 1024 },
    });

    wss.on("connection", (ws, req) => messageChannel.setChannel(ws, req));

    server.listen(port, "localhost");
    server.addListener("listening", () => {
      let address = server.address() as AddressInfo;
      console.log("server start", address.port);
    });
  }
  init(): Koa {
    const app = new Koa();
    this.initStaticService(app);
    this.initHttpAndWebSocketService(app);
    return app;
  }
}
export let horse = new Horse();
