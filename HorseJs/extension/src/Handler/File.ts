import { eventer } from '../eventer'
import { Base } from './Base'

export class File extends Base {
  className = 'File'
  isFolder(config: { path: string }) {
    return this.callHorse(this.isFolder, config)
  }
  getFileSize(config: { path: string }) {
    return this.callHorse(this.getFileSize, config)
  }
  getLastWriteTime(config: { path: string }) {
    return this.callHorse(this.getLastWriteTime, config)
  }
  readFile(config: { path: string; bufferSize?: number; onData: (data) => void }) {
    if (!config.bufferSize) config.bufferSize = 65536
    return new Promise((resolve, reject) => {
      let msgName = this.createMsgName(this.readFile)
      eventer.addOnceEventListener(msgName, (result) => {
        if (result.finished) {
          resolve(result)
        }
      })
      this.callHorseNative(msgName, JSON.stringify(config), (chunk: ArrayBuffer) => {
        config.onData(chunk)
      })
    })
  }
  writeFile(config: { path: string; data: string; existThen?: 'append' | 'cover' | 'error'; notExistThen?: 'create' | 'error' }) {
    if (!config.existThen) config.existThen = 'error'
    if (!config.notExistThen) config.notExistThen = 'create'
    return this.callHorse(this.writeFile, config)
  }
  readFileFromPosition(config: { path: string; position: number; bufferSize: number }) {
    return this.callHorse(this.readFileFromPosition, config)
  }
  copy(config: { src: string; dest: string }) {
    return this.callHorse(this.copy, config)
  }
}
