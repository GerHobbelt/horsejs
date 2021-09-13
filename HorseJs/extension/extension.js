var horse;
(() => {
  // src/Util.ts
  var Util = class {
    static randomNum(len = 12) {
      return Math.floor(Math.pow(10, len) * Math.random());
    }
    static sleep(timeSpan = 600) {
      return new Promise((r) => setTimeout(r, timeSpan));
    }
    static debounce(fn, span = 360) {
      let timer = null;
      return function() {
        clearTimeout(timer);
        timer = setTimeout(() => fn.apply(this, arguments), span);
      };
    }
    static throttle(fn, span = 360) {
      let timer = null;
      return function() {
        if (timer)
          return;
        timer = setTimeout(() => {
          fn.apply(this, arguments);
          timer = null;
        }, span);
      };
    }
    static callHorse(msgName, ...otherParams) {
      __callHorseFunc(msgName, ...otherParams);
    }
  };

  // src/Handler/Eventer.ts
  var _Eventer = class {
    static emitEvent(msgName, result) {
      if (!_Eventer.dic[msgName])
        return;
      _Eventer.dic[msgName].forEach((func) => func(result));
    }
    static addEventListener(msgName, cb) {
      if (!this.dic[msgName])
        this.dic[msgName] = [cb];
      else
        this.dic[msgName].push(cb);
    }
  };
  var Eventer = _Eventer;
  Eventer.dic = {};

  // src/Handler/Dialog.ts
  var Dialog = class {
    getFirstArgument(method) {
      return `${Dialog.name}_${method.name}_${Util.randomNum()}`;
    }
    openFile({ title, defaultFilePath, filters, lastFilterIndex }) {
      return new Promise((resolve, reject) => {
        let msgName = this.getFirstArgument(this.openFile);
        console.log(msgName);
        Eventer.addEventListener(msgName, (result) => {
          resolve(result);
        });
        Util.callHorse(msgName, title, defaultFilePath, filters, lastFilterIndex);
      });
    }
    openFolder({ title, defaultFilePath, filters, lastFilterIndex, cb }) {
      return new Promise((resolve, reject) => {
        let msgName = this.getFirstArgument(this.openFolder);
        Eventer.addEventListener(msgName, (result) => {
          resolve(result);
        });
        Util.callHorse(msgName, title, defaultFilePath, filters, lastFilterIndex);
      });
    }
  };

  // src/Handler/Info.ts
  var Info = class {
    constructor() {
      this.horseVersion = "0.0.1";
      this.appVersion = "0.0.1";
      this.osName = "win";
      this.osArch = "x64";
    }
  };

  // src/Handler/Window.ts
  var Window = class {
    constructor() {
      this.isMaximized = false;
      this.isMaximized = this.getIsMaximized();
      window.addEventListener("resize", Util.debounce(() => {
        let curState = this.getIsMaximized();
        let oldState = this.isMaximized;
        console.log(oldState, curState, this.isMaximized);
        this.isMaximized = curState;
        console.log(oldState, curState, this.isMaximized);
        if (oldState && !curState)
          Eventer.emitEvent("unMaximize");
        else if (!oldState && curState)
          Eventer.emitEvent("maximize");
      }));
    }
    getFirstArgument(method) {
      return `${Window.name}_${method.name}_${Util.randomNum()}`;
    }
    getIsMaximized() {
      return window.outerHeight === screen.availHeight && window.outerWidth === screen.availWidth;
    }
    maximize() {
      let arg = this.getFirstArgument(this.maximize);
      Util.callHorse(arg);
    }
    minimize() {
      let arg = this.getFirstArgument(this.minimize);
      Util.callHorse(arg);
    }
    close() {
      let arg = this.getFirstArgument(this.close);
      Util.callHorse(arg);
    }
    restore() {
      let arg = this.getFirstArgument(this.restore);
      Util.callHorse(arg);
    }
    hide() {
      let arg = this.getFirstArgument(this.hide);
      Util.callHorse(arg);
    }
    show() {
      let arg = this.getFirstArgument(this.show);
      Util.callHorse(arg);
    }
    resize(width, height) {
      let arg = this.getFirstArgument(this.resize);
      Util.callHorse(arg);
    }
    addEventListener(eventName, cb) {
      Eventer.addEventListener(eventName, cb);
    }
  };

  // src/main.ts
  var Horse = class {
    constructor() {
      this.__nativeMsgPipe = Eventer.__nativeMsgPipe;
      this.window = new Window();
      this.dialog = new Dialog();
      this.info = new Info();
    }
  };
  horse = new Horse();
})();
