# 文件

使用默认应用程序管理文件和 url

## 方法

- 获取某个目录下的所有路径

如果目标目录下包含文件和子目录，那么这些文件和子目录的路径都会被获取到

此方法并不会递归的获取目标路径下的子目录里的内容

如下代码中 result.data 为一个数组，数组里包含获取到的结果

```javascript
let result = await horse.file.readDir({ folderPath: "c://" });
```
