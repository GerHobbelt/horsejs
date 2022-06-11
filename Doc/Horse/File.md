# 获取某个文件的体积大小

```javascript
let result = await horse.file.getFileSize({ path: "c://a.zip" });
console.log(result.data);
```

# 判断一个路径是否为目录

```javascript
let result = await horse.file.isFolder({ path: "c://a.zip" });
console.log(result.data);
```

# 获取文件的最后一次编辑时间

```javascript
let result = await horse.file.getLastWriteTime({ path: "c://a.zip" });
console.log(result.data);
```

# 读取一个文件的全部内容

这个方法会分批读取目标文件，每成功读取一段数据就会触发 onData 方法。

当所有数据读取完成之后，readFile 异步方法结束，返回的 result 里包含最后一片数据。

- bufferSize 参数为一次读取的字节数

如果开发者没有提供这个值，那么它的默认值为 65536（64kb）

- path 目标文件路径

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

# 从指定位置读取文件的一片数据

- bufferSize 为数据片的大小

- position 为读取的起始位置

```javascript
let result = await horse.file.readFileFromPosition({
  path: folderResult.data[0],
  bufferSize: 65536,
  position: 3,
});
console.log(result.data);
```

# 写入文件

- path 为目标文件

- data 为待写入数据

- existThen 可能的值为：'append'， 'cover' ， 'error', 当文件存在时，如何写入文件

- notExistThen 可能的值为：'create' ， 'error',当文件不存在时，如何写入文件

```javascript
let result = await horse.file.writeFile({
  path: "c://1234.zip",
  data: `
      你好，世界
      안녕 세계
      Hello World
      `,
  existThen: "append",
  notExistThen: "create",
});
```

# 拷贝文件

- src 为目标文件路径

- dest 为被拷贝到的路径

如果 dest 路径文件已经存在，则会被覆盖

```javascript
await horse.file.copy({ src, dest });
```
