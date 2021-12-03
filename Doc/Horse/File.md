# 文件

使用默认应用程序管理文件和 url

## 方法

- 获取某个目录下的所有路径

如果目标目录下包含文件和子目录，那么这些文件和子目录的路径都会被获取到

此方法并不会递归的获取目标路径下的子目录里的内容

如下代码中 result.data 为一个数组，数组里包含获取到的结果

```javascript
let result = await horse.file.readDir({ path: "c://" });
console.log(result.data);
```

- 获取某个文件的体积大小

```javascript
let result = await horse.file.getFileSize({ path: "c://a.zip" });
console.log(result.data);
```

- 判断一个路径是否为目录

```javascript
let result = await horse.file.isFolder({ path: "c://a.zip" });
console.log(result.data);
```

- 获取文件的最后一次编辑时间

```javascript
let result = await horse.file.getLastWriteTime({ path: "c://a.zip" });
console.log(result.data);
```

- 读取一个文件的全部内容

这个方法会分批读取目标文件，每成功读取一段数据就会触发 onData 方法。

当所有数据读取完成之后，readFile 异步方法结束，返回 result。

bufferSize 参数就是一次读取的字节数，

如果开发者没有提供这个值，那么它的默认值为 65536（64kb）

```javascript
let result = await horse.file.readFile({
  path: folderResult.data[0],
  bufferSize: 65536,
  onData: (data) => {
    demoLog(data);
  },
});
console.log(result.data);
```

- 从指定位置读取文件的一片数据

bufferSize 为数据片的大小

position 为读取的起始位置

```javascript
let result = await horse.file.readFileFromPosition({
  path: folderResult.data[0],
  bufferSize: 65536,
  position: 3,
});
console.log(result.data);
```
