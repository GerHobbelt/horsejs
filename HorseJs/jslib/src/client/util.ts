export class Util {
  static randomNum(len = 12) {
    return Math.floor(Math.pow(10, len) * Math.random());
  }
  static sleep(timeSpan = 600) {
    return new Promise((r) => setTimeout(r, timeSpan));
  }
  //防抖  后注册的函数执行
  static debounce(fn: Function, span = 360) {
    let timer: null | number = null;
    return () => {
      //@ts-ignore
      clearTimeout(timer);
      timer = window.setTimeout(() => fn.apply(this, arguments), span);
    };
  }
  //限流  先注册的函数执行
  static throttle(fn: Function, span = 360): Function {
    let timer: null | number = null;
    return () => {
      if (timer != null) return;
      timer = window.setTimeout(() => {
        fn.apply(this, arguments);
        timer = null;
      }, span);
    };
  }
}
