class MessageChannel {
  onWebSocketMessage(msg: string) {
    console.log(msg);
  }
  init() {
    let url = new URL(location.href);
    let wsAddress = url.searchParams.get("ws") as string;
    url = new URL(wsAddress);
    url.searchParams.set("client", "client");
    let ws = new WebSocket(url.toString());
    ws.onopen = () => {
      console.log("websocket connected", url.toString());
    };
    ws.onmessage = (e) => this.onWebSocketMessage(e.data.toString());
    ws.onclose = () => {
      console.log("websocket closed");
    };
  }
}
export let messageChannel = new MessageChannel();
