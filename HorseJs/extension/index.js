native function jsFunc();
var horse = {
	__events:{
		__addEventListener:function(name,cb){
			if(!horse.__events[name]) horse.__events[name] = []
			horse.__events[name].push(cb);
		},
		__removeEventListener:function(name,cb){
			if(!horse.__events[name]) return;
			if(!cb) {
				delete horse.__events[name]
			}else{
				let index = horse.__events[name].indexOf(cb);
				if(index < 0) return;
				horse.__events[name].splice(index,1)
			}
		}
	},
  versionInfo: {
    version: "0.0.1",
  },
  window: {
    maximize: function () {
		return jsFunc(`window_${arguments.callee.name}`);
    },
	minimize: function () {
		return jsFunc(`window_${arguments.callee.name}`);
	},
	close: function () {
		return jsFunc(`window_${arguments.callee.name}`);
	},
	restore: function () {
		return jsFunc(`window_${arguments.callee.name}`);
	},
	hide: function () {
		return jsFunc(`window_${arguments.callee.name}`);
	},
	show: function () {
		return jsFunc(`window_${arguments.callee.name}`);
	},
	resize: function (width,height) {
		return jsFunc(`window_${arguments.callee.name}`,width,height);
	},
	addEventListener:function(name,cb){
		horse.__events.__addEventListenner(`window_${name}`,cb);
	},
	removeEventListener:function(name,cb){
		horse.__events.__removeEventListenner(`window_${name}`,cb);
	}
  },
  dialog:{

  }  
};
console.log("121212")
