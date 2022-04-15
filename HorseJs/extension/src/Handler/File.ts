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
  readFile(config: { path: string; bufferSize?: number; onData: (data) => void; onDataFinish: (data) => void }) {
    if (!config.bufferSize) config.bufferSize = 65536
    return new Promise((resolve, reject) => {
      let msgName = this.createMsgName(this.readFile)
      let dataMsgName = msgName + '_data'
      eventer.addEventListener(dataMsgName, (chunk) => {
        config.onData(chunk)
      })
      eventer.addOnceEventListener(msgName, (result) => {
        resolve(result)
      })
      eventer.addOnceEventListener(dataMsgName + '_finish', (result) => {
        eventer.removeEventListener(dataMsgName)
        config.onDataFinish(result)
        if (!result.success) {
          throw new Error(result.info)
        }
      })
      this.callHorseNative(msgName, JSON.stringify(config))
    })
  }
  writeFile(config: { path: string; data: string; existThen?: 'append' | 'cover' | 'error'; notExistThen?: 'create' | 'error' }) {
    if (!config.existThen) config.existThen = 'error'
    if (!config.notExistThen) config.notExistThen = 'create'
    return this.callHorse(this.writeFile, config)
  }
  readFileFromPosition(config: { path: string; position: number; bufferSize: number; onData: (data) => void; onDataFinish: (data) => void }) {
    return new Promise((resolve, reject) => {
      let msgName = this.createMsgName(this.readFileFromPosition)
      eventer.addOnceEventListener(msgName + '_data', (chunk) => {
        config.onData(chunk)
      })
      eventer.addOnceEventListener(msgName + '_data_finish', (result) => {
        config.onDataFinish(result)
        if (!result.success) {
          throw new Error(result.info)
        }
      })
      eventer.addOnceEventListener(msgName, (result) => {
        resolve(result)
      })
      this.callHorseNative(msgName, JSON.stringify(config))
    })
  }
  copy(config: { src: string; dest: string }) {
    return this.callHorse(this.copy, config)
  }
}
