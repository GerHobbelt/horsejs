<script lang="ts" setup>
let windowSizeChange = () => {}
let hideShowWindow = () => {}
let maximizeWindow = () => {}
let restoreWindow = () => {}
let minimizeWindow = () => {}
let closeWindow = () => {}
let openWindow = () => {}
let centerWindow = () => {}
let openDevTool = () => {}
let closeDevTool = () => {}
</script>
<template>
  <div id="sectionWindow" class="section sectionSelected">
    <div class="demoBtn" @click="windowSizeChange">改变窗口大小到800*600</div>
    <div class="demoBtn" @click="hideShowWindow">窗口隐藏，3秒钟之后窗口再显示</div>
    <div class="demoBtn" @click="maximizeWindow">最大化窗口</div>
    <div class="demoBtn" @click="restoreWindow">还原窗口</div>
    <div class="demoBtn" @click="minimizeWindow">最小化窗口</div>
    <div class="demoBtn" @click="closeWindow">关闭窗口</div>
    <div class="demoBtn" @click="openWindow">打开一个新窗口</div>
    <div class="demoBtn" @click="centerWindow">移动窗口到屏幕中央</div>
    <div class="demoBtn" @click="openDevTool">打开调试器窗口</div>
    <div class="demoBtn" @click="closeDevTool">关闭调试器窗口</div>
  </div>
</template>
<style lang="scss" scoped>
.demoBtn {
  display: inline-block;
  margin: 8px 8px;
  border-radius: 3px;
  padding: 0px 12px;
  border: 1px solid rgb(140, 200, 255);
  cursor: pointer;
  height: 36px;
  line-height: 36px;
}
.demoBtn:hover {
  background: rgb(33, 136, 255);
  border: 1px solid rgb(33, 136, 255);
  color: #fff;
}
.demoBtn:active {
  background: rgb(3, 102, 214);
  border: 1px solid rgb(3, 102, 214);
  color: #fff;
}
</style>
