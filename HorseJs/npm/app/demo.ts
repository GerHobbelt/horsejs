import { horse } from '../src/main'
import { ClipBoard } from './demo/Clipboard'
import { Db } from './demo/Db'
import { Dialog } from './demo/Dialog'
import { File } from './demo/File'
import { Info } from './demo/Info'
import { Menu } from './demo/Menu'
import { Path } from './demo/Path'
import { System } from './demo/System'
import { Tray } from './demo/Tray'
import { Window } from './demo/Window'
import './common'
let $ = (selector) => document.querySelector(selector)
class Demo {
  private dic = {
    [ClipBoard.className]: new ClipBoard(),
    [Db.className]: new Db(),
    [Dialog.className]: new Dialog(),
    [File.className]: new File(),
    [Info.className]: new Info(),
    [Menu.className]: new Menu(),
    [Path.className]: new Path(),
    [System.className]: new System(),
    [Tray.className]: new Tray(),
    [Window.className]: new Window(),
  }
  private menuEventInit() {
    $('#menuContainer').addEventListener('click', (e) => {
      let id = e.target.getAttribute('id')
      if (!id || e.target.classList.contains('menuSelected')) return
      $('.menuSelected').classList.remove('menuSelected')
      e.target.classList.add('menuSelected')
      $('.sectionSelected').classList.remove('sectionSelected')
      $(`#${id.replace('menu', 'section')}`).classList.add('sectionSelected')
    })
  }
  private linkBtnEventInit() {
    $('#sectionCodeLink').addEventListener('click', () => {
      let codeFileName = $('.menuSelected').getAttribute('id').replace('menu', '').toLowerCase()
      let target = `https://gitee.com/horsejs/horsejs/blob/master/HorseJs/app/demo/${codeFileName}.ts`
      horse.system.openExternal({ target, workingDir: '' })
    })
    $('#openDevToolBtn').addEventListener('click', async () => {
      await horse.window.openDevTool()
    })
    $('#openDocument').addEventListener('click', async () => {
      let codeFileName = $('.menuSelected').getAttribute('id').replace('menu', '')
      let target = `https://gitee.com/horsejs/horsejs/blob/master/Doc/Horse/${codeFileName}.md`
      horse.system.openExternal({ target, workingDir: '' })
    })
  }
  private demoBtnEventInit() {
    $('#demoContainer').addEventListener('click', async (e) => {
      if (!e.target.classList.contains('demoBtn')) return
      let id = e.target.getAttribute('id')
      let parentId = e.target.parentElement.getAttribute('id')
      parentId = parentId.replace('section', '')
      this.dic[parentId][id]()
    })
  }
  async init() {
    this.menuEventInit()
    this.linkBtnEventInit()
    this.demoBtnEventInit()
    await horse.window.openDevTool()
  }
  constructor() {}
}
window.addEventListener('load', async () => {
  let demo = new Demo()
  demo.init()
})
