var horse;
(() => {
  // extension/src/eventer.ts
  var Eventer = class {
    constructor() {
      this.dic = {};
    }
    emitEvent(msgName, result) {
      if (!this.dic[msgName])
        return;
      this.dic[msgName].forEach((func) => func(result));
    }
    addEventListener(msgName, cb) {
      if (!this.dic[msgName])
        this.dic[msgName] = [cb];
      else
        this.dic[msgName].push(cb);
    }
    addOnceEventListener(msgName, cb) {
      let cbWrap = (result) => {
        let index = this.dic[msgName].findIndex((v) => v == cbWrap);
        if (index >= 0)
          this.dic[msgName].splice(index, 1);
        cb(result);
      };
      if (!this.dic[msgName])
        this.dic[msgName] = [cbWrap];
      else
        this.dic[msgName].push(cbWrap);
    }
    removeEventListener(msgName, cb) {
      if (!this.dic[msgName] || this.dic[msgName].length < 1)
        return;
      if (!cb) {
        delete this.dic[msgName];
        return;
      }
      let index = this.dic[msgName].findIndex((v) => v == cb);
      if (index >= 0)
        this.dic[msgName].splice(index, 1);
    }
  };
  var eventer = new Eventer();

  // extension/src/Util.ts
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
  };

  // extension/src/Handler/Base.ts
  var Base = class {
    createMsgName(method) {
      return `${this.constructor.name}_${method.name}_${Util.randomNum()}`;
    }
    callHorseNative(msgName, ...otherParams) {
      __callHorseFunc(msgName, ...otherParams);
    }
    callHorse(method, config) {
      return new Promise((resolve, reject) => {
        let msgName = this.createMsgName(method);
        eventer.addOnceEventListener(msgName, (result) => resolve(result));
        this.callHorseNative(msgName, JSON.stringify(config));
      });
    }
  };

  // extension/src/Handler/Dialog.ts
  var Dialog = class extends Base {
    openFile(config) {
      return this.callHorse(this.openFile, config);
    }
    openFolder(config) {
      return this.callHorse(this.openFolder, config);
    }
  };

  // extension/src/Handler/Info.ts
  var Info = class extends Base {
    constructor() {
      super(...arguments);
      this.horseVersion = "0.0.1";
      this.appVersion = "0.0.1";
      this.osName = "win";
      this.osArch = "x64";
    }
    getPath(config) {
      return this.callHorse(this.getPath, config);
    }
    getAppInfo() {
      return this.callHorse(this.getAppInfo, {});
    }
    getHorseInfo() {
      return this.callHorse(this.getHorseInfo, {});
    }
  };

  // extension/src/Handler/Window.ts
  var Window = class extends Base {
    constructor() {
      super();
      this.isMaximized = false;
      this.processMaximizeEvent();
      this.processShowEvent();
    }
    processMaximizeEvent() {
      this.isMaximized = this.getIsMaximized();
      window.addEventListener("resize", Util.debounce(() => {
        let curState = this.getIsMaximized();
        let oldState = this.isMaximized;
        this.isMaximized = curState;
        if (oldState && !curState)
          eventer.emitEvent(`${Window.name}_unMaximize`);
        else if (!oldState && curState)
          eventer.emitEvent(`${Window.name}_maximize`);
      }));
    }
    processShowEvent() {
      document.addEventListener("visibilitychange", () => {
        if (document.hidden)
          eventer.emitEvent(`${Window.name}_hide`);
        else
          eventer.emitEvent(`${Window.name}_show`);
      });
    }
    open(config) {
      return this.callHorse(this.open, config);
    }
    addEventListener(eventName, cb) {
      eventer.addEventListener(`${Window.name}_${eventName}`, cb);
    }
    removeEventListener(eventName, cb) {
      eventer.removeEventListener(`${Window.name}_${eventName}`, cb);
    }
    getIsMaximized() {
      return window.outerHeight === screen.availHeight && window.outerWidth === screen.availWidth;
    }
    maximize() {
      return this.callHorse(this.maximize, {});
    }
    minimize() {
      return this.callHorse(this.minimize, {});
    }
    close() {
      return this.callHorse(this.close, {});
    }
    restore() {
      return this.callHorse(this.restore, {});
    }
    hide() {
      return this.callHorse(this.hide, {});
    }
    show() {
      return this.callHorse(this.show, {});
    }
    resize(config) {
      return this.callHorse(this.resize, config);
    }
  };

  // extension/src/Handler/Shell.ts
  var Shell = class extends Base {
    openExternal(config) {
      return this.callHorse(this.openExternal, config);
    }
  };

  // extension/src/Handler/Clipboard.ts
  var Clipboard = class extends Base {
    getData(config) {
      return this.callHorse(this.getData, config);
    }
    setData(config) {
      return this.callHorse(this.setData, config);
    }
  };

  // extension/src/Handler/File.ts
  var File = class extends Base {
    readDir(config) {
      return this.callHorse(this.readDir, config);
    }
    isFolder(config) {
      return this.callHorse(this.isFolder, config);
    }
    getFileSize(config) {
      return this.callHorse(this.getFileSize, config);
    }
    getLastWriteTime(config) {
      return this.callHorse(this.getLastWriteTime, config);
    }
    readFile(config) {
      if (!config.bufferSize)
        config.bufferSize = 65536;
      return new Promise((resolve, reject) => {
        let msgName = this.createMsgName(this.readFile);
        eventer.addEventListener(msgName, (result) => {
          if (result.success) {
            config.onData(result.data);
          } else {
            reject("error");
          }
          if (result.finished) {
            delete result.data;
            resolve(result);
          }
        });
        this.callHorseNative(msgName, JSON.stringify(config));
      });
    }
    writeFile(config) {
      if (!config.existThen)
        config.existThen = "error";
      if (!config.notExistThen)
        config.notExistThen = "create";
      return this.callHorse(this.writeFile, config);
    }
    readFileFromPosition(config) {
      return this.callHorse(this.readFileFromPosition, config);
    }
    copy(config) {
      return this.callHorse(this.copy, config);
    }
  };

  // extension/src/Handler/Path.ts
  var Path = class {
    constructor() {
      this.splitDeviceRe = /^([a-zA-Z]:|[\\\/]{2}[^\\\/]+[\\\/]+[^\\\/]+)?([\\\/])?([\s\S]*?)$/;
      this.splitTailRe = /^([\s\S]*?)((?:\.{1,2}|[^\\\/]+?|)(\.[^.\/\\]*|))(?:[\\\/]*)$/;
    }
    splitPath(fileName) {
      let result = this.splitDeviceRe.exec(fileName);
      let device = (result[1] || "") + (result[2] || "");
      let tail = result[3] || "";
      let result2 = this.splitTailRe.exec(tail);
      let dir = result2[1];
      let basename = result2[2];
      let ext = result2[3];
      return [device, dir, basename, ext];
    }
    win32StatPath(path) {
      var result = this.splitDeviceRe.exec(path), device = result[1] || "", isUnc = !!device && device[1] !== ":";
      return {
        device,
        isUnc,
        isAbsolute: isUnc || !!result[2],
        tail: result[3]
      };
    }
    dirName(path) {
      var result = this.splitPath(path), root = result[0], dir = result[1];
      if (!root && !dir) {
        return ".";
      }
      if (dir) {
        dir = dir.substr(0, dir.length - 1);
      }
      return root + dir;
    }
    baseName(path, ext) {
      var f = this.splitPath(path)[2];
      if (ext && f.substr(-1 * ext.length) === ext) {
        f = f.substr(0, f.length - ext.length);
      }
      return f;
    }
    extName(path) {
      return this.splitPath(path)[3];
    }
    resolve(path) {
    }
  };

  // extension/src/main.ts
  var Horse = class {
    constructor() {
      this.window = new Window();
      this.dialog = new Dialog();
      this.info = new Info();
      this.shell = new Shell();
      this.eventer = eventer;
      this.clipboard = new Clipboard();
      this.file = new File();
      this.path = new Path();
    }
  };
  horse = new Horse();
})();
