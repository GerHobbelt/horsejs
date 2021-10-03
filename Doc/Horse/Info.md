# 属性

## 当前框架的版本号

```javascript
horse.info.horseVersion;
```

## 当前应用的版本号

```javascript
horse.info.appVersion;
```

## 当前系统名

```javascript
horse.info.osName;
```

## 当前系统架构

```javascript
horse.info.osArch;
```

# 方法

## 获取应用程序的信息

```js
let result = await horse.info.getAppInfo();
```

## 获取 HorseJs 框架的信息

```js
let result = await horse.info.getHorseInfo();
```
