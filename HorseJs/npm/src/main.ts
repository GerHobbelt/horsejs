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
import { Plugin } from './Handler/Plugin'
import { Db } from './Handler/Db'
declare let __callHorseFunc: (arg: (msgName: string, ...otherParams) => void) => void
class Horse {
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
  plugin = new Plugin()
  db = new Db()
  nativeCallBack(msgName: string, ...otherParams) {
    if (typeof otherParams[0] === 'string') {
      this.eventer.emitEvent(msgName, JSON.parse(otherParams[0]))
    } else {
      this.eventer.emitEvent(msgName, otherParams[0])
    }
  }
  constructor() {
    __callHorseFunc((...args) => this.nativeCallBack(...args))
  }
}
export let horse = new Horse()
