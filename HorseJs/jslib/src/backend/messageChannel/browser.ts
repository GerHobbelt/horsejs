import { WebSocket } from "ws";
export class Browser {
  ws: WebSocket;
  private onWebSocketMessage(msg) {
    console.log("on browser message: ", msg.toString("utf8"));
  }
  constructor(ws: WebSocket) {
    this.ws = ws;
    this.ws.send("hi");
    this.ws.on("message", (message) => this.onWebSocketMessage(message));
  }
}
