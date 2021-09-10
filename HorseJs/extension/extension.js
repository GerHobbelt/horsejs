native function __callHorseFunc();
native function __listenHorseFunc();
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
    static listenHorse(msgName, callBack) {
      __listenHorseFunc(msgName, callBack);
    }
  };

  // src/Handler/Dialog.ts
  var Dialog = class {
    getFirstArgument(method) {
      return `${Dialog.name}_${method.name}_${Util.randomNum()}`;
    }
    openFile({ title, defaultFilePath, filters, lastFilterIndex }) {
      let arg = this.getFirstArgument(this.openFile);
      Util.callHorse(arg, title, defaultFilePath, filters, lastFilterIndex);
    }
    openFolder({ title, defaultFilePath, filters, lastFilterIndex }) {
      let arg = this.getFirstArgument(this.openFolder);
      Util.callHorse(arg, title, defaultFilePath, filters, lastFilterIndex);
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
    getFirstArgument(method) {
      return `${Window.name}_${method.name}_${Util.randomNum()}`;
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
  };

  // src/main.ts
  var Horse = class {
    constructor() {
      this.window = new Window();
      this.dialog = new Dialog();
      this.info = new Info();
    }
  };
  horse = new Horse();
})();
