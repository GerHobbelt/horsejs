import { Client } from "./messageChannel/client";
import { Browser } from "./messageChannel/browser";
import { WebSocket } from "ws";
import { IncomingMessage } from "http";
class MessageChannel {
  private browser: Browser;
  private client: Client;
  setChannel(ws: WebSocket, req: IncomingMessage) {
    console.log("websocket connected:", req.url);
    if (req.url?.endsWith("browser")) {
      this.browser = new Browser(ws);
    } else {
      this.client = new Client(ws);
    }
  }
}
export let messageChannel = new MessageChannel();
