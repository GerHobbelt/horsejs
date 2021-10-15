import { Dialog } from './Handler/Dialog'
import { eventer } from './eventer'
import { Info } from './Handler/Info'
import { Window } from './Handler/Window'
import { Shell } from './Handler/Shell'
export class Horse {
  window: Window
  dialog: Dialog
  info: Info
  shell: Shell
  eventer = eventer
  constructor() {
    this.window = new Window()
    this.dialog = new Dialog()
    this.info = new Info()
    this.shell = new Shell()
  }
}
declare let horse: Horse
horse = new Horse()
