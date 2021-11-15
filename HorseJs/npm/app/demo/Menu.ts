import { horse } from '../../src/main'

export class Menu {
  static className = 'Menu'
  async popup() {
    let data = [
      { name: '苹果', id: 0 },
      { name: '梨子', id: 1 },
      {
        name: '香蕉->',
        id: 3,
        subMenu: [
          { name: '子菜单1', id: 10 },
          { name: '子菜单2', id: 11 },
        ],
      },
    ]
    let result = await horse.menu.popup({
      data,
      click: (id) => {
        console.log(`你点击的菜单ID为${id}`)
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