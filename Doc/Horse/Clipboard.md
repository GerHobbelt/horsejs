# 获取剪切板内的数据

参数说明：

- dataType：数据类型，可能的值为：text、file、html

如果 dataType 值为 file，返回的是一个数组，数组里是文件路径字符串

```javascript
let result = await horse.clipboard.getData({ dataType: "text" });
if (result.success) {
  alert(JSON.stringify(result.data));
} else {
  alert("error");
}
```

# 向剪切板写入数据

参数说明：

- dataType：数据类型，可能的值为：text、file、html

如果 dataType 值为 file，返回的是一个数组，数组里是文件路径字符串

```javascript
let result = await horse.clipboard.setData({
  dataType: "text",
  data: "yourData",
});
if (result.success) {
  alert(JSON.stringify(result.data));
} else {
  alert("error");
}
```
