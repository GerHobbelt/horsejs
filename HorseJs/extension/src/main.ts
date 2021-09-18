import { Dialog } from './Handler/Dialog'
import { eventer } from './eventer'
import { Info } from './Handler/Info'
import { Window } from './Handler/Window'
import { Shell } from './Handler/Shell'
import { Clipboard } from './Handler/Clipboard'
import { File } from './Handler/File'
export class Horse {
  window = new Window()
  dialog = new Dialog()
  info = new Info()
  shell = new Shell()
  eventer = eventer
  clipboard = new Clipboard()
  file = new File()
}
declare let horse: Horse
horse = new Horse()
