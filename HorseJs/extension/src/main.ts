import { Dialog } from "./Handler/Dialog";
import { Info } from "./Handler/Info";
import { Window } from "./Handler/Window";
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
