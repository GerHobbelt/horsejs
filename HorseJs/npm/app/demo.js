(() => {
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
    async popup(config) {
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
    }
  };

  // src/Handler/Tray.ts
  var Tray = class extends Base {
    constructor() {
      super(...arguments);
      this.className = "Tray";
      this.isInit = false;
    }
    async create(config) {
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
    }
    async destroy() {
      return new Promise((resolve, reject) => {
        let msgName = `${this.className}_destroy`;
        eventer.removeEventListener(msgName + "_tray");
        eventer.removeEventListener(msgName + "_menu");
        this.callHorseNative(msgName, `{}`);
        this.isInit = false;
      });
    }
    async resetIcon(config) {
      return this.callHorse(this.resetIcon, config);
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

  // app/demo/Clipboard.ts
  var ClipBoard = class {
    async getClipboardText() {
      let result = await horse.clipboard.getData({ dataType: "text" });
      console.log(result);
    }
    async getClipboardFile() {
      let result = await horse.clipboard.getData({ dataType: "file" });
      console.log(result);
    }
    async getClipboardHTML() {
      let result = await horse.clipboard.getData({ dataType: "html" });
      console.log(result);
    }
    async setClipboardText() {
      let result = await horse.clipboard.setData({
        dataType: "text",
        data: "\u6B64\u6587\u672C\u88AB\u5199\u5165\u526A\u5207\u677F"
      });
      console.log(result);
    }
    async setClipboardFile() {
      let fileResult = await horse.dialog.openFile({
        title: "test",
        defaultPath: "C:\\AMD",
        multiSelections: true,
        filters: ["*"],
        filterIndex: 0
      });
      let result = await horse.clipboard.setData({
        dataType: "file",
        data: fileResult.data
      });
      console.log(result);
    }
    async setClipboardHTML() {
      let result = await horse.clipboard.setData({
        dataType: "html",
        data: `<span style="color:red">\u6B64HTML\u88AB\u5199\u5165\u526A\u5207\u677F</span>`
      });
      console.log(result);
    }
  };
  ClipBoard.className = "Clipboard";

  // app/demo/Db.ts
  var Db2 = class {
    async openDb() {
      let result = await horse.db.open();
      console.log(result);
    }
    async closeDb() {
      let result = await horse.db.close();
      console.log(result);
    }
    async createTable() {
      let result = await horse.db.execute({
        sql: `CREATE TABLE Message(Message TEXT NOT NULL, fromUser CHAR(60) NOT NULL, toUser CHAR(60)  NOT NULL, sendTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP);`
      });
      console.log(result);
    }
    async insertData() {
      let sqls = [];
      let msgs = [
        {
          message: `\u5929\u63A5\u4E91\u6D9B\u8FDE\u6653\u96FE\uFF0C\u661F\u6CB3\u6B32\u8F6C\u5343\u5E06\u821E\u3002\u4EFF\u4F5B\u68A6\u9B42\u5F52\u5E1D\u6240\u3002\u95FB\u5929\u8BED\uFF0C\u6BB7\u52E4\u95EE\u6211\u5F52\u4F55\u5904\u3002 \u6211\u62A5\u8DEF\u957F\u55DF\u65E5\u66AE\uFF0C\u5B66\u8BD7\u8C29\u6709\u60CA\u4EBA\u53E5\u3002\u4E5D\u4E07\u91CC\u98CE\u9E4F\u6B63\u4E3E\u3002\u98CE\u4F11\u4F4F\uFF0C\u84EC\u821F\u5439\u53D6\u4E09\u5C71\u53BB\uFF01`,
          fromUser: `\u674E\u6E05\u7167`,
          toUser: "\u8F9B\u5F03\u75BE"
        },
        {
          message: `\u9189\u91CC\u6311\u706F\u770B\u5251\uFF0C\u68A6\u56DE\u5439\u89D2\u8FDE\u8425\u3002\u516B\u767E\u91CC\u5206\u9EBE\u4E0B\u7099\uFF0C\u4E94\u5341\u5F26\u7FFB\u585E\u5916\u58F0\u3002\u6C99\u573A\u79CB\u70B9\u5175\u3002 \u9A6C\u4F5C\u7684\u5362\u98DE\u5FEB\uFF0C\u5F13\u5982\u9739\u96F3\u5F26\u60CA\u3002\u4E86\u5374\u541B\u738B\u5929\u4E0B\u4E8B\uFF0C\u8D62\u5F97\u751F\u524D\u8EAB\u540E\u540D\u3002\u53EF\u601C\u767D\u53D1\u751F\uFF01`,
          fromUser: `\u8F9B\u5F03\u75BE`,
          toUser: "\u674E\u6E05\u7167"
        }
      ];
      for (let i = 0; i < 100; i++) {
        let msg = msgs[i % 2];
        sqls.push(`insert into Message(Message, fromUser, toUser) values ('${msg.message}','${msg.fromUser}','${msg.toUser}');`);
      }
      let result = await horse.db.execute({
        sql: sqls.join("")
      });
      console.log(result);
    }
    async selectData() {
      let result = await horse.db.execute({
        sql: `select rowid,* from  Message where rowid = 88 or rowid = 65;`
      });
      console.log(result);
    }
    async deleteData() {
      let result = await horse.db.execute({
        sql: `delete from  Message where rowid = 14;`
      });
      console.log(result);
    }
    async updateData() {
      let obj = {
        message: "\u6012\u53D1\u51B2\u51A0\uFF0C\u51ED\u680F\u5904\u3001\u6F47\u6F47\u96E8\u6B47\u3002\u62AC\u671B\u773C\u3001\u4EF0\u5929\u957F\u5578\uFF0C\u58EE\u6000\u6FC0\u70C8\u3002\u4E09\u5341\u529F\u540D\u5C18\u4E0E\u571F\uFF0C\u516B\u5343\u91CC\u8DEF\u4E91\u548C\u6708\u3002\u83AB\u7B49\u95F2\u3001\u767D\u4E86\u5C11\u5E74\u5934\uFF0C\u7A7A\u60B2\u5207\u3002 \u9756\u5EB7\u803B\uFF0C\u72B9\u672A\u96EA\u3002\u81E3\u5B50\u6068\uFF0C\u4F55\u65F6\u706D\u3002\u9A7E\u957F\u8F66\uFF0C\u8E0F\u7834\u8D3A\u5170\u5C71\u7F3A\u3002\u58EE\u5FD7\u9965\u9910\u80E1\u864F\u8089\uFF0C\u7B11\u8C08\u6E34\u996E\u5308\u5974\u8840\u3002\u5F85\u4ECE\u5934\u3001\u6536\u62FE\u65E7\u5C71\u6CB3\uFF0C\u671D\u5929\u9619\u3002",
        fromUser: "\u5CB3\u98DE",
        toUser: "\u8F9B\u5F03\u75BE"
      };
      let result = await horse.db.execute({
        sql: `update Message set Message = '${obj.message}',fromUser = '${obj.fromUser}',toUser='${obj.toUser}' where rowid = 16;`
      });
      console.log(result);
    }
  };
  Db2.className = "Db";

  // app/demo/Dialog.ts
  var Dialog2 = class {
    async openFile() {
      let result = await horse.dialog.openFile({
        title: "test",
        defaultPath: "C:\\Windows",
        multiSelections: false,
        filters: ["*"],
        filterIndex: 0
      });
      console.log(result);
    }
    async openMultiFile() {
      let result = await horse.dialog.openFile({
        title: "test",
        defaultPath: "C:\\Windows",
        multiSelections: true,
        filters: ["*"],
        filterIndex: 0
      });
      console.log(result);
    }
    async openFolder() {
      let result = await horse.dialog.openFolder({
        title: "test",
        defaultPath: "C:\\Windows",
        multiSelections: true,
        filters: ["*"],
        filterIndex: 0
      });
      console.log(result);
    }
  };
  Dialog2.className = "Dialog";

  // app/demo/File.ts
  var File2 = class {
    async getLastWriteTime() {
      let fileResult = await horse.dialog.openFile({
        title: "\u8BF7\u4F60\u5148\u9009\u62E9\u4E00\u4E2A\u6587\u4EF6~~~",
        defaultPath: "C:\\",
        multiSelections: false,
        filters: ["*"],
        filterIndex: 0
      });
      let result = await horse.file.getLastWriteTime({
        path: fileResult.data[0]
      });
      console.log(result);
    }
    async getFileSize() {
      let fileResult = await horse.dialog.openFile({
        title: "\u8BF7\u4F60\u5148\u9009\u62E9\u4E00\u4E2A\u6587\u4EF6~~~",
        defaultPath: "C:\\",
        multiSelections: false,
        filters: ["*"],
        filterIndex: 0
      });
      if (!fileResult.data)
        return;
      let result = await horse.file.getFileSize({ path: fileResult.data[0] });
      console.log(result);
    }
    async readFile() {
      let fileResult = await horse.dialog.openFile({
        title: "\u8BF7\u4F60\u5148\u9009\u62E9\u4E00\u4E2A\u6587\u4EF6~~~",
        defaultPath: "C:\\",
        multiSelections: false,
        filters: ["*"],
        filterIndex: 0
      });
      if (!fileResult.data)
        return;
      let decoder = new TextDecoder("utf-8");
      let result = await horse.file.readFile({
        path: fileResult.data[0],
        bufferSize: 65536,
        onData: (chunk) => {
          let fileData = decoder.decode(chunk);
          console.log("\u6587\u4EF6\u6570\u636E\u7247\uFF1A", fileData);
        },
        onDataFinish: (result2) => {
          console.log("\u8BFB\u53D6\u6587\u4EF6\u5B8C\u6210\uFF1A", result2);
        }
      });
      console.log("\u8BF7\u6C42\u8BFB\u53D6\u6587\u4EF6\uFF1A", result);
    }
    async readFileFromPosition() {
      let fileResult = await horse.dialog.openFile({
        title: "\u8BF7\u4F60\u5148\u9009\u62E9\u4E00\u4E2A\u6587\u4EF6~~~",
        defaultPath: "C:\\",
        multiSelections: false,
        filters: ["*"],
        filterIndex: 0
      });
      if (!fileResult.data)
        return;
      let decoder = new TextDecoder("utf-8");
      let result = await horse.file.readFileFromPosition({
        path: fileResult.data[0],
        bufferSize: 65536,
        position: 6,
        onData: (chunk) => {
          let fileData = decoder.decode(chunk);
          console.log("\u6587\u4EF6\u6570\u636E\u7247\uFF1A", fileData);
        },
        onDataFinish: (result2) => {
          console.log("\u8BFB\u53D6\u6587\u4EF6\u5B8C\u6210\uFF1A", result2);
        }
      });
      console.log(result);
    }
    async writeFile() {
      let fileResult = await horse.dialog.openFile({
        title: "\u8BF7\u4F60\u5148\u9009\u62E9\u4E00\u4E2A\u6587\u4EF6~~~",
        defaultPath: "C:\\",
        multiSelections: false,
        filters: ["*"],
        filterIndex: 0
      });
      if (!fileResult.data)
        return;
      let result = await horse.file.writeFile({
        path: fileResult.data[0],
        data: `
          \u4F60\u597D\uFF0C\u4E16\u754C
          \uC548\uB155 \uC138\uACC4
          Hello World
          `,
        existThen: "append"
      });
      console.log(result);
    }
    async writeFileCreate() {
      let folderResult = await horse.dialog.openFolder({
        title: "\u8BF7\u4F60\u5148\u9009\u62E9\u4E00\u4E2A\u76EE\u5F55~~~",
        defaultPath: "C:\\",
        multiSelections: false,
        filters: ["*"],
        filterIndex: 0
      });
      if (!folderResult.data)
        return;
      let name = Math.floor(Math.pow(10, 6) * Math.random());
      let path = horse.path.join(folderResult.data[0], `${name}.txt`);
      let result = await horse.file.writeFile({
        path,
        data: `
          \u4F60\u597D\uFF0C\u4E16\u754C
          \uC548\uB155 \uC138\uACC4
          Hello World
          `,
        existThen: "append",
        notExistThen: "create"
      });
      console.log(result);
    }
    async copyFile() {
      let srcResult = await horse.dialog.openFile({
        title: "\u8BF7\u9009\u62E9\u5F85\u62F7\u8D1D\u7684\u6587\u4EF6",
        defaultPath: "C:\\",
        multiSelections: false,
        filters: ["*"],
        filterIndex: 0
      });
      if (!srcResult.data)
        return;
      let destResult = await horse.dialog.openFolder({
        title: "\u8BF7\u9009\u62E9\u62F7\u8D1D\u76EE\u6807\u76EE\u5F55",
        defaultPath: "C:\\",
        multiSelections: false,
        filters: ["*"],
        filterIndex: 0
      });
      if (!destResult.data)
        return;
      let src = srcResult.data[0];
      let baseName = horse.path.baseName(src);
      let dest = destResult.data[0] + baseName;
      let result = await horse.file.copy({ src, dest });
      console.log(result);
    }
  };
  File2.className = "File";

  // app/demo/Info.ts
  var Info2 = class {
    async getAppInfo() {
      let result = await horse.info.getAppInfo();
      console.log(result);
    }
    async getHorseInfo() {
      let result = await horse.info.getHorseInfo();
      console.log(result);
    }
    async getOSInfo() {
      let result = await horse.info.getOSInfo();
      console.log(result);
    }
    async getHardwareInfo() {
      let result = await horse.info.getHardwareInfo();
      console.log(result);
    }
    async getNetInfo() {
      let result = await horse.info.getNetInfo();
      console.log(result);
    }
    async getUserInfo() {
      let result = await horse.info.getUserInfo();
      console.log(result);
    }
  };
  Info2.className = "Info";

  // app/demo/Menu.ts
  var Menu2 = class {
    async popup() {
      let data = [
        { name: "\u82F9\u679C", id: 0 },
        { name: "\u68A8\u5B50", id: 1 },
        {
          name: "\u9999\u8549->",
          id: 3,
          subMenu: [
            { name: "\u5B50\u83DC\u53551", id: 10 },
            { name: "\u5B50\u83DC\u53552", id: 11 }
          ]
        }
      ];
      let result = await horse.menu.popup({
        data,
        click: (id) => {
          console.log(`\u4F60\u70B9\u51FB\u7684\u83DC\u5355ID\u4E3A${id}`);
        }
      });
      console.log(result);
    }
    async popupAtPoint() {
      let data = [
        { name: "test1", id: 0 },
        { name: "\u6D4B\u8BD5\u6D4B\u8BD5", id: 10 },
        { name: "\u6D4B\u8BD5\u6D4B\u8BD5", id: 100 }
      ];
      let result = await horse.menu.popup({
        data,
        position: { x: 200, y: 300 },
        click: (id) => {
          console.log(`\u4F60\u70B9\u51FB\u7684\u83DC\u5355ID\u4E3A${id}`);
        }
      });
      console.log(result);
    }
  };
  Menu2.className = "Menu";

  // app/demo/Path.ts
  var Path2 = class {
    async readDir() {
      let folderResult = await horse.dialog.openFolder({
        title: "\u8BF7\u4F60\u5148\u9009\u62E9\u4E00\u4E2A\u76EE\u5F55~~~",
        defaultPath: "C:\\",
        multiSelections: false,
        filters: ["*"],
        filterIndex: 0
      });
      if (!folderResult.data)
        return;
      let result = await horse.path.readDir({ path: folderResult.data[0] });
      console.log(result);
    }
    async getDesktopPath() {
      let result = await horse.path.getPath({
        name: "desktop"
      });
      console.log(result);
    }
    async getAppDataPath() {
      let result = await horse.path.getPath({
        name: "appData"
      });
      console.log(result);
    }
    async getExePath() {
      let result = await horse.path.getPath({
        name: "exePath"
      });
      console.log(result);
    }
    async getTempPath() {
      let result = await horse.path.getPath({
        name: "temp"
      });
      console.log(result);
    }
    async getDirName() {
      let result = await horse.path.getPath({
        name: "exePath"
      });
      let data = horse.path.dirName(result.data);
      console.log(data);
    }
    async getExtName() {
      let result = await horse.path.getPath({
        name: "exePath"
      });
      let data = horse.path.extName(result.data);
      console.log(data);
    }
    async isFolder() {
      let fileResult = await horse.dialog.openFile({
        title: "\u8BF7\u4F60\u5148\u9009\u62E9\u4E00\u4E2A\u6587\u4EF6~~~",
        defaultPath: "C:\\",
        multiSelections: false,
        filters: ["*"],
        filterIndex: 0
      });
      let result = await horse.path.isFolder({
        path: fileResult.data[0]
      });
      console.log(result);
    }
    async join() {
      let result = horse.path.join(`C:\\Windows\\System32`, "..\\SysWOW64\\apds.dll");
      console.log(`C:\\Windows\\System32\u4E0E..\\SysWOW64\\apds.dll\u5408\u5E76\u7ED3\u679C\uFF1A`, result);
    }
    async create() {
      let folderResult = await horse.dialog.openFolder({
        title: "\u8BF7\u4F60\u5148\u9009\u62E9\u4E00\u4E2A\u76EE\u5F55~~~",
        defaultPath: "C:\\",
        multiSelections: false,
        filters: ["*"],
        filterIndex: 0
      });
      if (!folderResult.data)
        return;
      let path = horse.path.join(folderResult.data[0], `newFolderName`);
      let result = await horse.path.create({ path });
      console.log(result);
    }
  };
  Path2.className = "Path";

  // app/demo/System.ts
  var System2 = class {
    async setAutoStart() {
      let result = await horse.system.autoStart({
        setOrRemove: "set"
      });
      console.log(result);
    }
    async removeAutoStart() {
      let result = await horse.system.autoStart({
        setOrRemove: "remove"
      });
      console.log(result);
    }
    async setProtocol() {
      let result = await horse.system.protocolClient({
        protocolName: "horse",
        setOrRemove: "set"
      });
      console.log(result);
    }
    async removeProtocol() {
      let result = await horse.system.protocolClient({
        protocolName: "horse",
        setOrRemove: "remove"
      });
      console.log(result);
    }
    async sendNotify() {
      let result = await horse.system.notify({
        title: "\u60A8\u6536\u5230\u65B0\u7684\u6D88\u606F",
        body: "\u6B64\u4E3A\u6D88\u606F\u7684\u6B63\u6587",
        click: () => {
          console.log("\u7528\u6237\u70B9\u51FB\u4E86\u7CFB\u7EDF\u6D88\u606F");
        },
        dismiss: () => {
          console.log("\u7CFB\u7EDF\u901A\u77E5\u6D88\u5931\u4E86");
        }
      });
      console.log(result);
    }
    async openUrlWithDefaultBrowser() {
      horse.system.openExternal({
        target: "https://gitee.com/horsejs/horsejs",
        workingDir: ""
      });
    }
  };
  System2.className = "System";

  // app/demo/Tray.ts
  var Tray2 = class {
    async create() {
      let menu = [{ name: "test1" }, { name: "\u6D4B\u8BD5\u6D4B\u8BD5" }, { name: "\u6D4B\u8BD5\u6D4B\u8BD5" }];
      let exePath = await horse.path.getPath({ name: "exePath" });
      let iconPath = horse.path.dirName(exePath.data) + "\\icon.ico";
      let result = await horse.tray.create({
        iconPath,
        tip: "\u8FD9\u662F\u56FE\u6807\u63D0\u793A",
        menu,
        menuClick: (index) => {
          console.log(`\u4F60\u70B9\u51FB\u4E86\u7B2C${index}\u4E2A\u83DC\u5355`);
        },
        leftButtonDown: () => {
          console.log("\u6258\u76D8\u56FE\u6807\u4E8B\u4EF6");
        }
      });
      console.log(result);
    }
    async resetIcon() {
      let exePath = await horse.path.getPath({ name: "exePath" });
      let iconPath = horse.path.dirName(exePath.data) + "\\icon2.ico";
      let tip = `\u8FD9\u662F\u56FE\u6807\u63D0\u793A`;
      let result = await horse.tray.resetIcon({ iconPath, tip });
      console.log(result);
    }
    async destroy() {
      let result = await horse.tray.destroy();
      console.log(result);
    }
  };
  Tray2.className = "Tray";

  // app/demo/Window.ts
  var Window2 = class {
    async windowSizeChange() {
      let result = await horse.window.resize({ width: 800, height: 600 });
      console.log(result);
    }
    async hideShowWindow() {
      let result = await horse.window.hide();
      setTimeout(() => {
        horse.window.show();
      }, 3e3);
      console.log(result);
    }
    async maximizeWindow() {
      let result = await horse.window.maximize();
      console.log(result);
    }
    async restoreWindow() {
      let result = await horse.window.restore();
      console.log(result);
    }
    async minimizeWindow() {
      let result = await horse.window.minimize();
      console.log(result);
    }
    async closeWindow() {
      let result = await horse.window.close();
      console.log(result);
    }
    async centerWindow() {
      let result = await horse.window.center();
      console.log(result);
    }
    async openDevTool() {
      let result = await horse.window.openDevTool();
      console.log(result);
    }
    async closeDevTool() {
      let result = await horse.window.closeDevTool();
      console.log(result);
    }
  };
  Window2.className = "Window";

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
    constructor() {
      this.dic = {
        [ClipBoard.className]: new ClipBoard(),
        [Db2.className]: new Db2(),
        [Dialog2.className]: new Dialog2(),
        [File2.className]: new File2(),
        [Info2.className]: new Info2(),
        [Menu2.className]: new Menu2(),
        [Path2.className]: new Path2(),
        [System2.className]: new System2(),
        [Tray2.className]: new Tray2(),
        [Window2.className]: new Window2()
      };
    }
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
        let codeFileName = $(".menuSelected").getAttribute("id").replace("menu", "");
        let target = `https://gitee.com/horsejs/horsejs/blob/master/HorseJs/npm/app/demo/${codeFileName}.ts`;
        horse.system.openExternal({ target, workingDir: "" });
      });
      $("#openDevToolBtn").addEventListener("click", async () => {
        await horse.window.openDevTool();
      });
      $("#openDocument").addEventListener("click", async () => {
        let codeFileName = $(".menuSelected").getAttribute("id").replace("menu", "");
        let target = `https://gitee.com/horsejs/horsejs/blob/master/Doc/Horse/${codeFileName}.md`;
        horse.system.openExternal({ target, workingDir: "" });
      });
    }
    demoBtnEventInit() {
      $("#demoContainer").addEventListener("click", async (e) => {
        if (!e.target.classList.contains("demoBtn"))
          return;
        let id = e.target.getAttribute("id");
        let parentId = e.target.parentElement.getAttribute("id");
        parentId = parentId.replace("section", "");
        this.dic[parentId][id]();
      });
    }
    async init() {
      this.menuEventInit();
      this.linkBtnEventInit();
      this.demoBtnEventInit();
      await horse.window.openDevTool();
    }
  };
  window.addEventListener("load", async () => {
    let demo = new Demo();
    demo.init();
  });
})();
