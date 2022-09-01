import EventEmitter from 'events'
import { WebSocket } from 'ws'
export class BrowserMessageChannel extends EventEmitter {
  ws: WebSocket
  private onWebSocketMessage(message) {
    let msg = JSON.parse(message.toString('utf8'))
    // console.log('eventName', eventName)
    this.emit(msg['__msgId'].toString(), msg)
  }
  sendMessage(message: any) {
    let msgStr = JSON.stringify(message)
    this.ws.send(msgStr)
  }
  init(ws: WebSocket) {
    this.ws = ws
    this.ws.on('message', (message) => this.onWebSocketMessage(message))
  }
}
export let browserMessageChannel = new BrowserMessageChannel()
