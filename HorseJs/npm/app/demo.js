(() => {
  var __async = (__this, __arguments, generator) => {
    return new Promise((resolve, reject) => {
      var fulfilled = (value) => {
        try {
          step(generator.next(value));
        } catch (e) {
          reject(e);
        }
      };
      var rejected = (value) => {
        try {
          step(generator.throw(value));
        } catch (e) {
          reject(e);
        }
      };
      var step = (x) => x.done ? resolve(x.value) : Promise.resolve(x.value).then(fulfilled, rejected);
      step((generator = generator.apply(__this, __arguments)).next());
    });
  };

  // src/eventer.ts
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
  };

  // src/Handler/Base.ts
  var Base = class {
    constructor() {
      this.className = "Base";
    }
    createMsgName(method) {
      return `${this.className}_${method.name}_${Util.randomNum()}`;
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

  // src/Handler/Dialog.ts
  var Dialog = class extends Base {
    constructor() {
      super(...arguments);
      this.className = "Dialog";
    }
    openFile(config) {
      return this.callHorse(this.openFile, config);
    }
    openFolder(config) {
      return this.callHorse(this.openFolder, config);
    }
  };

  // src/Handler/Info.ts
  var Info = class extends Base {
    constructor() {
      super(...arguments);
      this.className = "Info";
    }
    getAppInfo() {
      return this.callHorse(this.getAppInfo, {});
    }
    getHorseInfo() {
      return this.callHorse(this.getHorseInfo, {});
    }
    getOSInfo() {
      return this.callHorse(this.getOSInfo, {});
    }
    getHardwareInfo() {
      return this.callHorse(this.getHardwareInfo, {});
    }
    getUserInfo() {
      return this.callHorse(this.getUserInfo, {});
    }
    getNetInfo() {
      return this.callHorse(this.getNetInfo, {});
    }
  };

  // src/Handler/Window.ts
  var Window = class extends Base {
    constructor() {
      super();
      this.className = "Window";
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
          eventer.emitEvent(`${this.className}_unMaximize`);
        else if (!oldState && curState)
          eventer.emitEvent(`${this.className}_maximize`);
      }));
    }
    processShowEvent() {
      document.addEventListener("visibilitychange", () => {
        if (document.hidden)
          eventer.emitEvent(`${this.className}_hide`);
        else
          eventer.emitEvent(`${this.className}_show`);
      });
    }
    open(config) {
      if (!config.width)
        config.width = 1e3;
      if (!config.height)
        config.height = 800;
      return this.callHorse(this.open, config);
    }
    addEventListener(eventName, cb) {
      eventer.addEventListener(`${this.className}_${eventName}`, cb);
    }
    removeEventListener(eventName, cb) {
      eventer.removeEventListener(`${this.className}_${eventName}`, cb);
    }
    getIsMaximized() {
      let hSpan = window.outerHeight - screen.availHeight;
      let wSpan = window.outerWidth - screen.availWidth;
      return Math.abs(hSpan) < 2 && Math.abs(wSpan) < 2;
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
    center() {
      return this.callHorse(this.center, {});
    }
    openDevTool() {
      return this.callHorse(this.openDevTool, {});
    }
    closeDevTool() {
      return this.callHorse(this.closeDevTool, {});
    }
  };

  // src/Handler/Clipboard.ts
  var Clipboard = class extends Base {
    constructor() {
      super(...arguments);
      this.className = "Clipboard";
    }
    getData(config) {
      return this.callHorse(this.getData, config);
    }
    setData(config) {
      return this.callHorse(this.setData, config);
    }
  };

  // src/Handler/File.ts
  var File = class extends Base {
    constructor() {
      super(...arguments);
      this.className = "File";
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
        let dataMsgName = msgName + "_data";
        eventer.addEventListener(dataMsgName, (chunk) => {
          config.onData(chunk);
        });
        eventer.addOnceEventListener(msgName, (result) => {
          resolve(result);
        });
        eventer.addOnceEventListener(dataMsgName + "_finish", (result) => {
          eventer.removeEventListener(dataMsgName);
          config.onDataFinish(result);
          if (!result.success) {
            throw new Error(result.info);
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
      return new Promise((resolve, reject) => {
        let msgName = this.createMsgName(this.readFileFromPosition);
        eventer.addOnceEventListener(msgName + "_data", (chunk) => {
          config.onData(chunk);
        });
        eventer.addOnceEventListener(msgName + "_data_finish", (result) => {
          config.onDataFinish(result);
          if (!result.success) {
            throw new Error(result.info);
          }
        });
        eventer.addOnceEventListener(msgName, (result) => {
          resolve(result);
        });
        this.callHorseNative(msgName, JSON.stringify(config));
      });
    }
    copy(config) {
      return this.callHorse(this.copy, config);
    }
  };

  // src/Handler/Path.ts
  var Path = class extends Base {
    constructor() {
      super(...arguments);
      this.className = "Path";
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
    normalizeArray(parts, allowAboveRoot) {
      var res = [];
      for (var i = 0; i < parts.length; i++) {
        var p = parts[i];
        if (!p || p === ".")
          continue;
        if (p === "..") {
          if (res.length && res[res.length - 1] !== "..") {
            res.pop();
          } else if (allowAboveRoot) {
            res.push("..");
          }
        } else {
          res.push(p);
        }
      }
      return res;
    }
    normalizeUNCRoot(device) {
      return "\\\\" + device.replace(/^[\\\/]+/, "").replace(/[\\\/]+/g, "\\");
    }
    normalize(path) {
      var result = this.win32StatPath(path), device = result.device, isUnc = result.isUnc, isAbsolute = result.isAbsolute, tail = result.tail, trailingSlash = /[\\\/]$/.test(tail);
      tail = this.normalizeArray(tail.split(/[\\\/]+/), !isAbsolute).join("\\");
      if (!tail && !isAbsolute) {
        tail = ".";
      }
      if (tail && trailingSlash) {
        tail += "\\";
      }
      if (isUnc) {
        device = this.normalizeUNCRoot(device);
      }
      return device + (isAbsolute ? "\\" : "") + tail;
    }
    readDir(config) {
      return this.callHorse(this.readDir, config);
    }
    create(config) {
      return this.callHorse(this.create, config);
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
    getPath(config) {
      return this.callHorse(this.getPath, config);
    }
    isFolder(config) {
      return this.callHorse(this.isFolder, config);
    }
    join(...args) {
      var joined = args.join("\\");
      if (!/^[\\\/]{2}[^\\\/]/.test(args[0])) {
        joined = joined.replace(/^[\\\/]{2,}/, "\\");
      }
      return this.normalize(joined);
    }
  };

  // src/Handler/System.ts
  var System = class extends Base {
    constructor() {
      super(...arguments);
      this.className = "System";
    }
    autoStart(config) {
      return this.callHorse(this.autoStart, config);
    }
    protocolClient(config) {
      return this.callHorse(this.protocolClient, config);
    }
    notify(config) {
      return new Promise((resolve, reject) => {
        let msgName = this.createMsgName(this.notify);
        eventer.addOnceEventListener(msgName, (result) => {
          resolve({ success: true });
        });
        eventer.addOnceEventListener(msgName + "_event", (result) => {
          config[result.type]();
        });
        this.callHorseNative(msgName, JSON.stringify(config));
      });
    }
    openExternal(config) {
      return this.callHorse(this.openExternal, config);
    }
  };

  // src/Handler/Menu.ts
  var Menu = class extends Base {
    constructor() {
      super(...arguments);
      this.className = "Menu";
    }
    popup(config) {
      return __async(this, null, function* () {
        if (!config.position) {
          config.position = { x: -1, y: -1 };
        }
        return new Promise((resolve, reject) => {
          let msgName = this.createMsgName(this.popup);
          eventer.addOnceEventListener(msgName, (result) => {
            resolve({ success: true });
          });
          eventer.addOnceEventListener(msgName + "_event", (result) => {
            config.click(result.id);
          });
          this.callHorseNative(msgName, JSON.stringify(config));
        });
      });
    }
  };

  // src/Handler/Tray.ts
  var Tray = class extends Base {
    constructor() {
      super(...arguments);
      this.className = "Tray";
      this.isInit = false;
    }
    create(config) {
      return __async(this, null, function* () {
        if (this.isInit) {
          throw new Error("\u5DF2\u7ECF\u521B\u5EFA\u4E86\u4E00\u4E2A\u6258\u76D8\u56FE\u6807");
          return;
        }
        return new Promise((resolve, reject) => {
          let msgName = `${this.className}_create`;
          eventer.addOnceEventListener(msgName, (result) => {
            resolve({ success: true });
          });
          eventer.removeEventListener(msgName + "_tray");
          eventer.removeEventListener(msgName + "_menu");
          eventer.addEventListener(msgName + "_tray", (result) => {
            if (!config[result.clickType])
              return;
            config[result.clickType]();
          });
          eventer.addEventListener(msgName + "_menu", (result) => {
            config.menuClick(result.index);
          });
          this.callHorseNative(msgName, JSON.stringify(config));
          this.isInit = true;
        });
      });
    }
    destroy() {
      return __async(this, null, function* () {
        return new Promise((resolve, reject) => {
          let msgName = `${this.className}_destroy`;
          eventer.removeEventListener(msgName + "_tray");
          eventer.removeEventListener(msgName + "_menu");
          this.callHorseNative(msgName, `{}`);
          this.isInit = false;
        });
      });
    }
    resetIcon(config) {
      return __async(this, null, function* () {
        return this.callHorse(this.resetIcon, config);
      });
    }
  };

  // src/Handler/Plugin.ts
  var Plugin = class extends Base {
    constructor() {
      super(...arguments);
      this.className = "Plugin";
    }
    load(config) {
      return this.callHorse(this.load, config);
    }
    excute(config) {
      return this.callHorse(this.excute, config);
    }
    unload(config) {
      return this.callHorse(this.unload, config);
    }
  };

  // src/Handler/Db.ts
  var Db = class extends Base {
    constructor() {
      super(...arguments);
      this.className = "Db";
    }
    open() {
      return this.callHorse(this.open, {});
    }
    close() {
      return this.callHorse(this.close, {});
    }
    execute(config) {
      return this.callHorse(this.execute, config);
    }
  };

  // src/main.ts
  var Horse = class {
    constructor() {
      this.window = new Window();
      this.dialog = new Dialog();
      this.info = new Info();
      this.eventer = eventer;
      this.clipboard = new Clipboard();
      this.file = new File();
      this.path = new Path();
      this.system = new System();
      this.menu = new Menu();
      this.tray = new Tray();
      this.plugin = new Plugin();
      this.db = new Db();
      __callHorseFunc((...args) => this.nativeCallBack(...args));
    }
    nativeCallBack(msgName, ...otherParams) {
      if (typeof otherParams[0] === "string") {
        this.eventer.emitEvent(msgName, JSON.parse(otherParams[0]));
      } else {
        this.eventer.emitEvent(msgName, otherParams[0]);
      }
    }
  };
  var horse = new Horse();

  // app/common.ts
  var Common = class {
    titleBarEventInit() {
      let btnArr = document.querySelector(".titleTool").children;
      btnArr[0].addEventListener("click", () => {
        horse.window.minimize();
      });
      btnArr[1].addEventListener("click", () => {
        if (btnArr[1].classList.contains("horse-restore")) {
          horse.window.restore();
        } else {
          horse.window.maximize();
        }
      });
      btnArr[2].addEventListener("click", () => {
        horse.window.close();
      });
      horse.window.addEventListener("maximize", () => {
        btnArr[1].classList.remove("horse-maximize");
        btnArr[1].classList.add("horse-restore");
      });
      horse.window.addEventListener("unMaximize", () => {
        btnArr[1].classList.remove("horse-restore");
        btnArr[1].classList.add("horse-maximize");
      });
    }
    constructor() {
      window.addEventListener("load", () => {
        this.titleBarEventInit();
      });
    }
  };
  var common = new Common();

  // app/demo.ts
  var $ = (selector) => document.querySelector(selector);
  var Demo = class {
    menuEventInit() {
      $("#menuContainer").addEventListener("click", (e) => {
        let id = e.target.getAttribute("id");
        if (!id || e.target.classList.contains("menuSelected"))
          return;
        $(".menuSelected").classList.remove("menuSelected");
        e.target.classList.add("menuSelected");
        $(".sectionSelected").classList.remove("sectionSelected");
        $(`#${id.replace("menu", "section")}`).classList.add("sectionSelected");
      });
    }
    linkBtnEventInit() {
      $("#sectionCodeLink").addEventListener("click", () => {
        let codeFileName = $(".menuSelected").getAttribute("id").replace("menu", "").toLowerCase();
        let target = `https://gitee.com/horsejs/horsejs/blob/master/HorseJs/app/demo/${codeFileName}.js`;
        horse.system.openExternal({ target, workingDir: "" });
      });
      $("#openDevToolBtn").addEventListener("click", () => __async(this, null, function* () {
        yield horse.window.openDevTool();
      }));
      $("#openDocument").addEventListener("click", () => __async(this, null, function* () {
        let codeFileName = $(".menuSelected").getAttribute("id").replace("menu", "");
        let target = `https://gitee.com/horsejs/horsejs/blob/master/Doc/Horse/${codeFileName}.md`;
        horse.system.openExternal({ target, workingDir: "" });
      }));
    }
    demoBtnEventInit() {
      $("#demoContainer").addEventListener("click", (e) => __async(this, null, function* () {
        if (!e.target.classList.contains("demoBtn"))
          return;
        let id = e.target.getAttribute("id");
        let parentId = e.target.parentElement.getAttribute("id");
        parentId = parentId.replace("section", "").toLowerCase();
      }));
    }
    init() {
      return __async(this, null, function* () {
        this.menuEventInit();
        this.linkBtnEventInit();
        this.demoBtnEventInit();
        yield horse.window.openDevTool();
      });
    }
    constructor() {
    }
  };
  window.addEventListener("load", () => __async(void 0, null, function* () {
    let demo = new Demo();
    demo.init();
  }));
})();