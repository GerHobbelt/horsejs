import { WebSocket } from 'ws'
export class BrowserMessageChannel {
  ws: WebSocket
  private onWebSocketMessage(msg) {
    console.log('on browser message: ', msg.toString('utf8'))
  }
  sendMessage(message: any) {
    this.ws.send(JSON.stringify(message))
  }
  init(ws: WebSocket) {
    this.ws = ws
    this.ws.on('message', (message) => this.onWebSocketMessage(message))
  }
}
export let browserMessageChannel = new BrowserMessageChannel()
