import { Dialog } from "./Dialog";
import { Info } from "./Info";
import { Window } from "./Window";
class Horse {
  window: Window;
  dialog: Dialog;
  info: Info;
  constructor() {
    this.window = new Window();
    this.dialog = new Dialog();
    this.info = new Info();
  }
}
// @ts-ignore
horse = new Horse();
