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
}
