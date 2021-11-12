import { horse } from '../../src/main'
export class Dialog {
  static className = 'Dialog'
  async openFile() {
    let result = await horse.dialog.openFile({
      title: 'test',
      defaultPath: 'C:\\Windows',
      multiSelections: false,
      filters: ['*'],
      filterIndex: 0,
    })
    console.log(result)
  }
  async openMultiFile() {
    let result = await horse.dialog.openFile({
      title: 'test',
      defaultPath: 'C:\\Windows',
      multiSelections: true,
      filters: ['*'],
      filterIndex: 0,
    })
    console.log(result)
  }
  async openFolder() {
    let result = await horse.dialog.openFolder({
      title: 'test',
      defaultPath: 'C:\\Windows',
      multiSelections: true,
      filters: ['*'],
      filterIndex: 0,
    })
    console.log(result)
  }
}
