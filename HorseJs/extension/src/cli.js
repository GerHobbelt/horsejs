let esbuild = require('esbuild')
let path = require('path')
let fs = require('fs')
let os = require('os')
let entryFilePath = path.join(process.cwd(), 'src/main.ts')
let outfile = path.join(process.cwd(), 'extension.js')
esbuild.buildSync({
  entryPoints: [entryFilePath],
  outfile,
  minify: false,
  bundle: true,
  sourcemap: false,
})
let pre = `var horse;` //native function __callHorseFunc();${os.EOL}
let js = `${pre}${os.EOL}${fs.readFileSync(outfile)}`
fs.writeFileSync(outfile, js)
let now = new Date()
console.log(`build ok  ${now.getHours()}:${now.getMinutes()}:${now.getSeconds()}`)

// native function jsFunc();
// var horse = {
// 	__events:{
// 		__addEventListener:function(name,cb){
// 			if(!horse.__events[name]) horse.__events[name] = []
// 			horse.__events[name].push(cb);
// 		},
// 		__removeEventListener:function(name,cb){
// 			if(!horse.__events[name]) return;
// 			if(!cb) {
// 				delete horse.__events[name]
// 			}else{
// 				let index = horse.__events[name].indexOf(cb);
// 				if(index < 0) return;
// 				horse.__events[name].splice(index,1)
// 			}
// 		}
// 	},
//   versionInfo: {
//     version: "0.0.1",
//   },
//   window: {
//     maximize: function () {
// 		return jsFunc(`window_${arguments.callee.name}`);
//     },
// 	minimize: function () {
// 		return jsFunc(`window_${arguments.callee.name}`);
// 	},
// 	close: function () {
// 		return jsFunc(`window_${arguments.callee.name}`);
// 	},
// 	restore: function () {
// 		return jsFunc(`window_${arguments.callee.name}`);
// 	},
// 	hide: function () {
// 		return jsFunc(`window_${arguments.callee.name}`);
// 	},
// 	show: function () {
// 		return jsFunc(`window_${arguments.callee.name}`);
// 	},
// 	resize: function (width,height) {
// 		return jsFunc(`window_${arguments.callee.name}`,width,height);
// 	},
// 	//todo
// 	addEventListener:function(name,cb){
// 		horse.__events.__addEventListenner(`window_${name}`,cb);
// 	},
// 	//todo
// 	removeEventListener:function(name,cb){
// 		horse.__events.__removeEventListenner(`window_${name}`,cb);
// 	}
//   },
//   dialog:{
// 	  openFile:function(option){
// 		  return jsFunc(`dialog_${arguments.callee.name}`,option.title,option.defaultFilePath,option.filters,option.lastFilterIndex);
// 	  },
// 	  openFolder:function({title,defaultFilePath,filters,lastFilterIndex}){
// 		  return jsFunc(`dialog_${arguments.callee.name}`,option.title,option.defaultFilePath,option.filters,option.lastFilterIndex);
// 	  }
//   }
// };
