import { horse } from '../src/main'
import './common'
let $ = (selector) => document.querySelector(selector)
class Demo {
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
      let target = `https://gitee.com/horsejs/horsejs/blob/master/HorseJs/app/demo/${codeFileName}.js`
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
      parentId = parentId.replace('section', '').toLowerCase()
      //   let { processor } = await import(`./demo/${parentId}.js`)
      //   processor[id]()
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