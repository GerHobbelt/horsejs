import { horse } from '../../src/main'
export class Path {
  static className = 'Path'
  async readDir() {
    let folderResult = await horse.dialog.openFolder({
      title: '请你先选择一个目录~~~',
      defaultPath: 'C:\\',
      multiSelections: false,
      filters: ['*'],
      filterIndex: 0,
    })
    if (!folderResult.data) return
    let result = await horse.path.readDir({ path: folderResult.data[0] })
    console.log(result)
  }
  async getDesktopPath() {
    let result = await horse.path.getPath({
      name: 'desktop',
    })
    console.log(result)
  }
  async getAppDataPath() {
    let result = await horse.path.getPath({
      name: 'appData',
    })
    console.log(result)
  }
  async getExePath() {
    let result = await horse.path.getPath({
      name: 'exePath',
    })
    console.log(result)
  }
  async getTempPath() {
    let result = await horse.path.getPath({
      name: 'temp',
    })
    console.log(result)
  }
  async getDirName() {
    let result = await horse.path.getPath({
      name: 'exePath',
    })
    let data = horse.path.dirName(result.data)
    console.log(data)
  }
  async getExtName() {
    let result = await horse.path.getPath({
      name: 'exePath',
    })
    let data = horse.path.extName(result.data)
    console.log(data)
  }
  async isFolder() {
    let fileResult = await horse.dialog.openFile({
      title: '请你先选择一个文件~~~',
      defaultPath: 'C:\\',
      multiSelections: false,
      filters: ['*'],
      filterIndex: 0,
    })
    let result = await horse.path.isFolder({
      path: fileResult.data[0],
    })
    console.log(result)
  }
  async join() {
    let result = horse.path.join(`C:\\Windows\\System32`, '..\\SysWOW64\\apds.dll')
    console.log(`C:\\Windows\\System32与..\\SysWOW64\\apds.dll合并结果：`, result)
  }
  async create() {
    let folderResult = await horse.dialog.openFolder({
      title: '请你先选择一个目录~~~',
      defaultPath: 'C:\\',
      multiSelections: false,
      filters: ['*'],
      filterIndex: 0,
    })
    if (!folderResult.data) return
    let path = horse.path.join(folderResult.data[0], `newFolderName`)
    let result = await horse.path.create({ path })
    console.log(result)
  }
}
