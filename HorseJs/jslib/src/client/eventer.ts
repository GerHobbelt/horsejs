class Eventer {
  private dic: { [key: string]: [Function] } = {};
  public emitEvent(msgName: string, result?: any) {
    if (!this.dic[msgName]) {
      console.warn("没有找到该事件的监听函数");
      return;
    }
    this.dic[msgName].forEach((func) => func(result));
  }
  public addEventListener(msgName: string, cb: Function) {
    if (!this.dic[msgName]) this.dic[msgName] = [cb];
    else this.dic[msgName].push(cb);
  }
  public addOnceEventListener(msgName: string, cb: Function) {
    let cbWrap = (result: any) => {
      let index = this.dic[msgName].findIndex((v) => v == cbWrap);
      if (index >= 0) this.dic[msgName].splice(index, 1);
      cb(result);
    };
    if (!this.dic[msgName]) this.dic[msgName] = [cbWrap];
    else this.dic[msgName].push(cbWrap);
  }
  public removeEventListener(msgName: string, cb?: Function) {
    if (!this.dic[msgName] || this.dic[msgName].length < 1) return;
    if (!cb) {
      delete this.dic[msgName];
      return;
    }
    let index = this.dic[msgName].findIndex((v) => v == cb);
    if (index >= 0) this.dic[msgName].splice(index, 1);
  }
}
export let eventer = new Eventer();
