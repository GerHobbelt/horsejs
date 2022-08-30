import { messageChannel } from "./client/messageChannel";
import { Window } from "./client/window";

class Horse {
  window = new Window();
  init() {
    messageChannel.init();
  }
}
export let horse = new Horse();
