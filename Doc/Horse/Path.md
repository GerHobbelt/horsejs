# 获取某个目录下的所有路径

如果目标目录下包含文件和子目录，那么这些文件和子目录的路径都会被获取到

此方法并不会递归的获取目标路径下的子目录里的内容

如下代码中 result.data 为一个数组，数组里包含获取到的结果

```javascript
let result = await horse.path.readDir({ path: "c://" });
```

# 获取系统路径

name 可能的值为：

- temp 临时文件夹
- exePath 当前的可执行文件
- desktop 当前用户的桌面文件夹
- documents 用户文档目录的路径
- downloads 用户下载目录的路径
- music 用户音乐目录的路径
- pictures 用户图片目录的路径
- videos 用户视频目录的路径

```js
let result = await horse.path.getPath({ name: "exePath" });
```

# 获取目录名

类似于 Unix dirname 命令。 尾随的目录分隔符被忽略，

```js
horse.path.dirname("/foo/bar/baz/asdf/quux");
// 返回: '/foo/bar/baz/asdf'
```

# 获取路径中的文件名

获取路径的最后一部分，类似于 Unix basename 命令。 尾随的目录分隔符被忽略

```js
horse.path.basename("/foo/bar/baz/asdf/quux.html");
// 返回: 'quux.html'
horse.horse.path.basename("/foo/bar/baz/asdf/quux.html", ".html");
// 返回: 'quux'
```

尽管 Windows 通常以不区分大小写的方式处理文件名（包括文件扩展名），但此函数不会。

```js
horse.path.basename("C:\\foo.html", ".html");
// 返回: 'foo'
horse.path.basename("C:\\foo.HTML", ".html");
// 返回: 'foo.HTML'
```

# 获取一个路径的扩展名

```js
horse.path.extname("index.html");
// 返回: '.html'
horse.path.extname("index.coffee.md");
// 返回: '.md'
horse.path.extname("index.");
// 返回: '.'
horse.path.extname("index");
// 返回: ''
horse.path.extname(".index");
// 返回: ''
horse.path.extname(".index.md");
// 返回: '.md'
```
