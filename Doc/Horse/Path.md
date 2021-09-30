# 文件

操作文件或目录的路径

## 方法

- 获取目录名

类似于 Unix dirname 命令。 尾随的目录分隔符被忽略，

```js
path.dirname("/foo/bar/baz/asdf/quux");
// 返回: '/foo/bar/baz/asdf'
```

- 获取路径中的文件名

获取路径的最后一部分，类似于 Unix basename 命令。 尾随的目录分隔符被忽略

```js
path.basename("/foo/bar/baz/asdf/quux.html");
// 返回: 'quux.html'
path.basename("/foo/bar/baz/asdf/quux.html", ".html");
// 返回: 'quux'
```

尽管 Windows 通常以不区分大小写的方式处理文件名（包括文件扩展名），但此函数不会。

```js
path.win32.basename("C:\\foo.html", ".html");
// 返回: 'foo'
path.win32.basename("C:\\foo.HTML", ".html");
// 返回: 'foo.HTML'
```

- 获取一个路径的扩展名

```js
path.extname("index.html");
// 返回: '.html'
path.extname("index.coffee.md");
// 返回: '.md'
path.extname("index.");
// 返回: '.'
path.extname("index");
// 返回: ''
path.extname(".index");
// 返回: ''
path.extname(".index.md");
// 返回: '.md'
```
