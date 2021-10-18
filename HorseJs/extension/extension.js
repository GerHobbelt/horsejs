var horse;
(()=>{var y=(o,e,t)=>new Promise((i,r)=>{var s=c=>{try{m(t.next(c))}catch(p){r(p)}},h=c=>{try{m(t.throw(c))}catch(p){r(p)}},m=c=>c.done?i(c.value):Promise.resolve(c.value).then(s,h);m((t=t.apply(o,e)).next())});var E=class{constructor(){this.dic={}}emitEvent(e,t){!this.dic[e]||this.dic[e].forEach(i=>i(t))}addEventListener(e,t){this.dic[e]?this.dic[e].push(t):this.dic[e]=[t]}addOnceEventListener(e,t){let i=r=>{let s=this.dic[e].findIndex(h=>h==i);s>=0&&this.dic[e].splice(s,1),t(r)};this.dic[e]?this.dic[e].push(i):this.dic[e]=[i]}removeEventListener(e,t){if(!this.dic[e]||this.dic[e].length<1)return;if(!t){delete this.dic[e];return}let i=this.dic[e].findIndex(r=>r==t);i>=0&&this.dic[e].splice(i,1)}},n=new E;var d=class{static randomNum(e=12){return Math.floor(Math.pow(10,e)*Math.random())}static sleep(e=600){return new Promise(t=>setTimeout(t,e))}static debounce(e,t=360){let i=null;return function(){clearTimeout(i),i=setTimeout(()=>e.apply(this,arguments),t)}}static throttle(e,t=360){let i=null;return function(){i||(i=setTimeout(()=>{e.apply(this,arguments),i=null},t))}}};var a=class{constructor(){this.className="Base"}createMsgName(e){return`${this.className}_${e.name}_${d.randomNum()}`}callHorseNative(e,...t){__callHorseFunc(e,...t)}callHorse(e,t){return new Promise((i,r)=>{let s=this.createMsgName(e);n.addOnceEventListener(s,h=>i(h)),this.callHorseNative(s,JSON.stringify(t))})}};var u=class extends a{constructor(){super(...arguments);this.className="Dialog"}openFile(e){return this.callHorse(this.openFile,e)}openFolder(e){return this.callHorse(this.openFolder,e)}};var f=class extends a{constructor(){super(...arguments);this.className="Info"}getAppInfo(){return this.callHorse(this.getAppInfo,{})}getHorseInfo(){return this.callHorse(this.getHorseInfo,{})}getOSInfo(){return this.callHorse(this.getOSInfo,{})}getHardwareInfo(){return this.callHorse(this.getHardwareInfo,{})}};var l=class extends a{constructor(){super();this.className="Window";this.isMaximized=!1;this.processMaximizeEvent(),this.processShowEvent()}processMaximizeEvent(){this.isMaximized=this.getIsMaximized(),window.addEventListener("resize",d.debounce(()=>{let e=this.getIsMaximized(),t=this.isMaximized;this.isMaximized=e,t&&!e?n.emitEvent(`${l.name}_unMaximize`):!t&&e&&n.emitEvent(`${l.name}_maximize`)}))}processShowEvent(){document.addEventListener("visibilitychange",()=>{document.hidden?n.emitEvent(`${l.name}_hide`):n.emitEvent(`${l.name}_show`)})}open(e){return this.callHorse(this.open,e)}addEventListener(e,t){n.addEventListener(`${l.name}_${e}`,t)}removeEventListener(e,t){n.removeEventListener(`${l.name}_${e}`,t)}getIsMaximized(){let e=window.outerHeight-screen.availHeight,t=window.outerWidth-screen.availWidth;return Math.abs(e)<2&&Math.abs(t)<2}maximize(){return this.callHorse(this.maximize,{})}minimize(){return this.callHorse(this.minimize,{})}close(){return this.callHorse(this.close,{})}restore(){return this.callHorse(this.restore,{})}hide(){return this.callHorse(this.hide,{})}show(){return this.callHorse(this.show,{})}resize(e){return this.callHorse(this.resize,e)}};var v=class extends a{constructor(){super(...arguments);this.className="Clipboard"}getData(e){return this.callHorse(this.getData,e)}setData(e){return this.callHorse(this.setData,e)}};var g=class extends a{constructor(){super(...arguments);this.className="File"}isFolder(e){return this.callHorse(this.isFolder,e)}getFileSize(e){return this.callHorse(this.getFileSize,e)}getLastWriteTime(e){return this.callHorse(this.getLastWriteTime,e)}readFile(e){return e.bufferSize||(e.bufferSize=65536),new Promise((t,i)=>{let r=this.createMsgName(this.readFile);n.addEventListener(r,s=>{s.success?e.onData(s.data):i("error"),s.finished&&(delete s.data,t(s))}),this.callHorseNative(r,JSON.stringify(e))})}writeFile(e){return e.existThen||(e.existThen="error"),e.notExistThen||(e.notExistThen="create"),this.callHorse(this.writeFile,e)}readFileFromPosition(e){return this.callHorse(this.readFileFromPosition,e)}copy(e){return this.callHorse(this.copy,e)}};var x=class extends a{constructor(){super(...arguments);this.className="Path";this.splitDeviceRe=/^([a-zA-Z]:|[\\\/]{2}[^\\\/]+[\\\/]+[^\\\/]+)?([\\\/])?([\s\S]*?)$/;this.splitTailRe=/^([\s\S]*?)((?:\.{1,2}|[^\\\/]+?|)(\.[^.\/\\]*|))(?:[\\\/]*)$/}splitPath(e){let t=this.splitDeviceRe.exec(e),i=(t[1]||"")+(t[2]||""),r=t[3]||"",s=this.splitTailRe.exec(r),h=s[1],m=s[2],c=s[3];return[i,h,m,c]}win32StatPath(e){var t=this.splitDeviceRe.exec(e),i=t[1]||"",r=!!i&&i[1]!==":";return{device:i,isUnc:r,isAbsolute:r||!!t[2],tail:t[3]}}readDir(e){return this.callHorse(this.readDir,e)}dirName(e){var t=this.splitPath(e),i=t[0],r=t[1];return!i&&!r?".":(r&&(r=r.substr(0,r.length-1)),i+r)}baseName(e,t){var i=this.splitPath(e)[2];return t&&i.substr(-1*t.length)===t&&(i=i.substr(0,i.length-t.length)),i}extName(e){return this.splitPath(e)[3]}getPath(e){return this.callHorse(this.getPath,e)}};var H=class extends a{constructor(){super(...arguments);this.className="System"}autoStart(e){return this.callHorse(this.autoStart,e)}protocolClient(e){return this.callHorse(this.protocolClient,e)}notify(e){return new Promise((t,i)=>{let r=this.createMsgName(this.notify);n.addOnceEventListener(r,s=>{t({success:!0})}),n.addOnceEventListener(r+"_event",s=>{e[s.type]()}),this.callHorseNative(r,JSON.stringify(e))})}openExternal(e){return this.callHorse(this.openExternal,e)}};var w=class extends a{constructor(){super(...arguments);this.className="Menu"}popup(e){return y(this,null,function*(){return e.position||(e.position={x:-1,y:-1}),new Promise((t,i)=>{let r=this.createMsgName(this.popup);n.addOnceEventListener(r,s=>{t({success:!0})}),n.addOnceEventListener(r+"_event",s=>{e.click(s.index)}),this.callHorseNative(r,JSON.stringify(e))})})}};var F=class extends a{constructor(){super(...arguments);this.className="Tray"}};var b=class{constructor(){this.window=new l;this.dialog=new u;this.info=new f;this.eventer=n;this.clipboard=new v;this.file=new g;this.path=new x;this.system=new H;this.menu=new w;this.tray=new F}};horse=new b;})();
