# 对话框

## 方法：

### 打开文件对话框

参数说明：

- title：对话框标题
- defaultFilePath：默认路径
- multiSelections：是否允许选择多个文件
- filters：文件过滤器

  这是一个数组

- lastFilterIndex：文件过滤器默认项

```javascript
let result = await horse.dialog.openFile({
  title: "test",
  defaultFilePath: "C:\\AMD",
  multiSelections: true,
  filters: ["*"],
  lastFilterIndex: 0,
});
```
