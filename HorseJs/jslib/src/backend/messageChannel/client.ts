import { WebSocket } from "ws";
export class Client {
  ws: WebSocket;
  private onWebSocketMessage(msg) {
    console.log("on client message: ", msg.toString("utf8"));
  }
  constructor(ws: WebSocket) {
    this.ws = ws;
    this.ws.on("message", (message) => this.onWebSocketMessage(message));
  }
}
