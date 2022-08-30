import { horse } from '../../src/main'

export class Menu {
  static className = 'Menu'
  menuData = [
    { name: '苹果', id: 0 },
    { name: '梨子', id: 1 },
    { type: 'separator', id: 2 },
    {
      name: '香蕉',
      id: 3,
      subMenu: [
        { name: '子菜单1', id: 30 },
        { name: '子菜单2', id: 31 },
      ],
    },
    { name: '凤梨', id: 4, type: 'check', checked: false },
    { name: '菠萝蜜', id: 5, type: 'check', checked: true, enable: false },
  ]
  async popup() {
    let result = await horse.menu.popup({
      data: this.menuData,
      click: (id) => {
        console.log(`你点击的菜单ID为${id}`)
        if (id === 4 || id == 5) {
          this.menuData[id].checked = !this.menuData[id].checked
        }
      },
    })
    console.log(result)
  }
  async popupAtPoint() {
    let data = [
      { name: 'test1', id: 0 },
      { name: '测试测试', id: 10 },
      { name: '测试测试', id: 100 },
    ]
    let result = await horse.menu.popup({
      data,
      position: { x: 200, y: 300 },
      click: (id) => {
        console.log(`你点击的菜单ID为${id}`)
      },
    })
    console.log(result)
  }
}
