import { Window } from "./client/window";

class Horse {
  window = new Window();
  init() {
    let ws = new WebSocket("ws://localhost:5916");
    ws.onopen = () => {
      ws.send("something");
    };
    ws.onmessage = (e) => {
      console.log("received: %s", e.data);
    };
    ws.onclose = () => {
      console.log("closed");
    };
  }
}
export let horse = new Horse();
