import { horse } from '../../src/main'
export class Tray {
  static className = 'Tray'
  async create() {
    let menu = [{ name: 'test1' }, { name: '测试测试' }, { name: '测试测试' }]
    let exePath = await horse.path.getPath({ name: 'exePath' })
    let iconPath = horse.path.dirName(exePath.data)
    iconPath = horse.path.join(iconPath, 'app/icon/icon.ico')
    let result = await horse.tray.create({
      iconPath,
      tip: '这是图标提示',
      menu,
      menuClick: (index) => {
        console.log(`你点击了第${index}个菜单`)
      },
      leftButtonDown: () => {
        console.log('托盘图标事件')
      },
    })
    console.log(result)
  }
  async resetIcon() {
    let exePath = await horse.path.getPath({ name: 'exePath' })
    let iconPath = horse.path.dirName(exePath.data)
    iconPath = horse.path.join(iconPath, 'app/icon/icon2.ico')
    let tip = `这是图标提示`
    let result = await horse.tray.resetIcon({ iconPath, tip })
    console.log(result)
  }
  async destroy() {
    let result = await horse.tray.destroy()
    console.log(result)
  }
}
