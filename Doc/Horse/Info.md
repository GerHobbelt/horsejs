# 获取应用程序的信息

此方法返回的就是配置文件提供的信息

```js
let result = await horse.info.getAppInfo();
console.log(result.data);
//{"appName":"HorseJs","autoShowFirstWindow":true,"sizeConfig":{"maxSize":{"height":-1,"width":-1},"miniSize":{"height":300,"width":400},"startSize":{"height":600,"width":800}},"startPath":"app/index.html","version":"0.0.1"}
```

# 获取 HorseJs 框架的信息

目前仅返回 HorseJs 的版本号

```js
let result = await horse.info.getHorseInfo();
console.log(result.data);
//{"HorseJsVersion":"0.0.2"}
```
