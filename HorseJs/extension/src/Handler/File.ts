import { eventer } from '../eventer'
import { Util } from '../Util'
import { Base } from './Base'

export class File extends Base {
  readDir(config: { path: string }) {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.readDir)
      eventer.addEventListener(msgName, (result) => resolve(result))
      Util.callHorse(msgName, JSON.stringify(config))
    })
  }
  isFolder(config: { path: string }) {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.isFolder)
      eventer.addEventListener(msgName, (result) => resolve(result))
      Util.callHorse(msgName, JSON.stringify(config))
    })
  }
  getFileSize(config: { path: string }) {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.getFileSize)
      eventer.addEventListener(msgName, (result) => resolve(result))
      Util.callHorse(msgName, JSON.stringify(config))
    })
  }
  getLastWriteTime(config: { path: string }) {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.getLastWriteTime)
      eventer.addEventListener(msgName, (result) => resolve(result))
      Util.callHorse(msgName, JSON.stringify(config))
    })
  }
  readFile(config: { path: string; bufferSize?: number; onData: (data) => void }) {
    if (!config.bufferSize) config.bufferSize = 65536
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.readFile)
      eventer.addEventListener(msgName, (result) => {
        if (result.success) {
          config.onData(result.data)
        } else {
          reject('error')
        }
        if (result.finished) {
          delete result.data
          resolve(result)
        }
      })
      Util.callHorse(msgName, JSON.stringify(config))
    })
  }
  writeFile(config: { path: string; data: string; existThen?: 'append' | 'cover' | 'error'; notExistThen?: 'create' | 'error' }) {
    if (!config.existThen) config.existThen = 'error'
    if (!config.notExistThen) config.notExistThen = 'create'
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.writeFile)
      eventer.addEventListener(msgName, (result) => resolve(result))
      Util.callHorse(msgName, JSON.stringify(config))
    })
  }
  readFileFromPosition(config: { path: string; position: number; bufferSize: number }) {
    return new Promise((resolve, reject) => {
      let msgName = this.getFirstArgument(this.readFileFromPosition)
      eventer.addEventListener(msgName, (result) => resolve(result))
      Util.callHorse(msgName, JSON.stringify(config))
    })
  }
}
