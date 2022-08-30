import { horse } from '../../src/main'
export class ClipBoard {
  static className = 'Clipboard'
  async getClipboardText() {
    let result = await horse.clipboard.getData({ dataType: 'text' })
    console.log(result)
  }
  async getClipboardFile() {
    let result = await horse.clipboard.getData({ dataType: 'file' })
    console.log(result)
  }
  async getClipboardHTML() {
    let result = await horse.clipboard.getData({ dataType: 'html' })
    console.log(result)
  }
  async setClipboardText() {
    let result = await horse.clipboard.setData({
      dataType: 'text',
      data: '此文本被写入剪切板',
    })
    console.log(result)
  }
  async setClipboardFile() {
    let fileResult = await horse.dialog.openFile({
      title: 'test',
      defaultPath: 'C:\\AMD',
      multiSelections: true,
      filters: ['*'],
      filterIndex: 0,
    })
    let result = await horse.clipboard.setData({
      dataType: 'file',
      data: fileResult.data,
    })
    console.log(result)
  }
  async setClipboardHTML() {
    let result = await horse.clipboard.setData({
      dataType: 'html',
      data: `<span style="color:red">此HTML被写入剪切板</span>`,
    })
    console.log(result)
  }
}
