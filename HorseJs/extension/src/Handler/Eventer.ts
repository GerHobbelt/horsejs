export class Eventer {
  private static dic: { [key: string]: [Function] } = {}
  public static emitEvent(msgName: string, result?) {
    if (!Eventer.dic[msgName]) return
    Eventer.dic[msgName].forEach((func) => func(result))
  }
  public static addEventListener(msgName: string, cb: Function) {
    if (!this.dic[msgName]) this.dic[msgName] = [cb]
    else this.dic[msgName].push(cb)
  }
  public static removeEventListener(msgName: string, cb: Function) {
    if (!this.dic[msgName] || this.dic[msgName].length < 1) return
    if (!cb) {
      delete this.dic[msgName]
      return
    }
    let index = this.dic[msgName].findIndex((v) => v == cb)
    if (index >= 0) this.dic[msgName].splice(index, 1)
  }
}
