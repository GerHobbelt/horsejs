import { Dialog } from './Handler/Dialog'
import { Eventer } from './Handler/Eventer'
import { Info } from './Handler/Info'
import { Window } from './Handler/Window'
export class Horse {
  window: Window
  dialog: Dialog
  info: Info
  eventer: Eventer
  constructor() {
    this.window = new Window()
    this.dialog = new Dialog()
    this.info = new Info()
  }
}
declare let horse: Horse
horse = new Horse()
