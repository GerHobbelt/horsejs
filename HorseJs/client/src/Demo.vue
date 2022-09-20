<template>
  <div class="demo">
    <div id="menuContainer">
      <a class="menuSelected" href="window">窗口</a>
      <a href="dialog">对话框</a>
      <a href="/demo/window">信息</a>
      <a href="/demo/window">剪切板</a>
      <a href="/demo/window">系统</a>
      <a href="/demo/window">文件</a>
      <a href="/demo/window">路径</a>
      <a href="/demo/window">菜单</a>
      <a href="/demo/window">托盘图标</a>
      <a href="/demo/window">数据库</a>
      <a href="/demo/window">原生插件</a>
    </div>
    <router-view />
  </div>
</template>
<style lang="scss" scoped>
.demo {
  color: #333;
  background: #fff;
  flex: 1;
  display: flex;
}
#menuContainer {
  background: rgb(219, 237, 255);
  width: 180px;
  line-height: 38px;
  font-size: 15px;
  padding: 12px 0px;
}
#menuContainer a {
  cursor: pointer;
  padding-left: 16px;
  border-left: 6px solid transparent;
  display: block;
  text-decoration: none;
  padding-left: 16px;
}
#menuContainer a:hover {
  background: rgb(140, 200, 255);
  color: #fff;
  border-left: 6px solid rgb(121, 184, 255);
}

#menuContainer .menuSelected {
  background: rgb(33, 136, 255) !important;
  color: #fff;
  border-left: 6px solid rgb(0, 92, 197) !important;
  position: relative;
}
#menuContainer .menuSelected::after {
  display: block;
  width: 0px;
  height: 0px;
  position: absolute;
  right: 0px;
  top: calc(50% - 4px);
  border-top: solid 4px transparent;
  border-right: solid 4px #fff;
  border-bottom: solid 4px transparent;
  content: "";
}
#demoContainer {
  flex: 1;
  display: flex;
  flex-direction: column;
  overflow: hidden;
}
</style>
