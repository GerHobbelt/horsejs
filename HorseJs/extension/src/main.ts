import { Dialog } from './Handler/Dialog'
import { eventer } from './eventer'
import { Info } from './Handler/Info'
import { Window } from './Handler/Window'
import { Shell } from './Handler/Shell'
import { Clipboard } from './Handler/Clipboard'
export class Horse {
  window = new Window()
  dialog = new Dialog()
  info = new Info()
  shell = new Shell()
  eventer = eventer
  clipboard = new Clipboard()
}
declare let horse: Horse
horse = new Horse()
