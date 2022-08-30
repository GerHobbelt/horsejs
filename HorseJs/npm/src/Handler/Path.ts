import { Base } from './Base'

export class Path extends Base {
  className = 'Path'
  private splitDeviceRe = /^([a-zA-Z]:|[\\\/]{2}[^\\\/]+[\\\/]+[^\\\/]+)?([\\\/])?([\s\S]*?)$/
  private splitTailRe = /^([\s\S]*?)((?:\.{1,2}|[^\\\/]+?|)(\.[^.\/\\]*|))(?:[\\\/]*)$/
  private splitPath(fileName: string) {
    let result = this.splitDeviceRe.exec(fileName)
    let device = (result[1] || '') + (result[2] || '')
    let tail = result[3] || ''
    let result2 = this.splitTailRe.exec(tail)
    let dir = result2[1]
    let basename = result2[2]
    let ext = result2[3]
    return [device, dir, basename, ext]
  }
  private win32StatPath(path) {
    var result = this.splitDeviceRe.exec(path),
      device = result[1] || '',
      isUnc = !!device && device[1] !== ':'
    return {
      device: device,
      isUnc: isUnc,
      isAbsolute: isUnc || !!result[2],
      tail: result[3],
    }
  }
  private normalizeArray(parts, allowAboveRoot) {
    var res = []
    for (var i = 0; i < parts.length; i++) {
      var p = parts[i]
      // ignore empty parts
      if (!p || p === '.') continue
      if (p === '..') {
        if (res.length && res[res.length - 1] !== '..') {
          res.pop()
        } else if (allowAboveRoot) {
          res.push('..')
        }
      } else {
        res.push(p)
      }
    }
    return res
  }
  private normalizeUNCRoot(device: string) {
    return '\\\\' + device.replace(/^[\\\/]+/, '').replace(/[\\\/]+/g, '\\')
  }
  private normalize(path: string) {
    var result = this.win32StatPath(path),
      device = result.device,
      isUnc = result.isUnc,
      isAbsolute = result.isAbsolute,
      tail = result.tail,
      trailingSlash = /[\\\/]$/.test(tail)
    tail = this.normalizeArray(tail.split(/[\\\/]+/), !isAbsolute).join('\\')

    if (!tail && !isAbsolute) {
      tail = '.'
    }
    if (tail && trailingSlash) {
      tail += '\\'
    }
    if (isUnc) {
      device = this.normalizeUNCRoot(device)
    }
    return device + (isAbsolute ? '\\' : '') + tail
  }
  readDir(config: { path: string }) {
    return this.callHorse(this.readDir, config)
  }
  create(config: { path: string }) {
    return this.callHorse(this.create, config)
  }
  dirName(path: string) {
    var result = this.splitPath(path),
      root = result[0],
      dir = result[1]
    if (!root && !dir) {
      return '.'
    }
    if (dir) {
      dir = dir.substr(0, dir.length - 1)
    }
    return root + dir
  }
  baseName(path: string, ext?: string) {
    var f = this.splitPath(path)[2]
    if (ext && f.substr(-1 * ext.length) === ext) {
      f = f.substr(0, f.length - ext.length)
    }
    return f
  }
  extName(path: string) {
    return this.splitPath(path)[3]
  }
  getPath(config: { name }) {
    return this.callHorse(this.getPath, config)
  }
  isFolder(config: { path: string }) {
    return this.callHorse(this.isFolder, config)
  }
  join(...args: string[]) {
    var joined = args.join('\\')
    if (!/^[\\\/]{2}[^\\\/]/.test(args[0])) {
      joined = joined.replace(/^[\\\/]{2,}/, '\\')
    }
    return this.normalize(joined)
  }
}
// todo 目前只支持windows
// https://github.com/jinder/path/blob/master/path.js
// https://github.com/browserify/path-browserify
