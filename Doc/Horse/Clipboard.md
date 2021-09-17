# 剪切板

## 方法：

### 获取剪切板内文本

参数说明：

- dataType：数据类型

```javascript
let result = await horse.clipboard.getData({ dataType: "text" });
if (result.success) {
  alert(JSON.stringify(result.data));
} else {
  alert("error");
}
```
