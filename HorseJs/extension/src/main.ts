import { Dialog } from './Handler/Dialog'
import { eventer } from './eventer'
import { Info } from './Handler/Info'
import { Window } from './Handler/Window'
import { Clipboard } from './Handler/Clipboard'
import { File } from './Handler/File'
import { Path } from './Handler/Path'
import { System } from './Handler/System'
import { Menu } from './Handler/Menu'
import { Tray } from './Handler/Tray'
export class Horse {
  window = new Window()
  dialog = new Dialog()
  info = new Info()
  eventer = eventer
  clipboard = new Clipboard()
  file = new File()
  path = new Path()
  system = new System()
  menu = new Menu()
  tray = new Tray()
}
declare let horse: Horse
horse = new Horse()
