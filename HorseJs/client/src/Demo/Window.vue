<script lang="ts" setup>
import { Win, WindowConfig } from '../../../jslib/src/client'
let win = Win.getCurrentWindow()
let windowSizeChange = async () => {
  await win.setSize({ width: 960, height: 800 })
}
let hideShowWindow = async () => {
  await win.hide()
  setTimeout(async () => {
    await win.show()
  }, 3000)
}
let maximizeWindow = async () => {
  await win.maximize()
}
let restoreWindow = async () => {
  await win.restore()
}
let minimizeWindow = async () => {
  await win.minimize()
}
let closeWindow = async () => {
  await win.close()
}
let openWindow = async () => {
  let config = new WindowConfig()
  config.title = '这是我的窗口！！！'
  config.frameless = true
  config.url = 'https://www.baidu.com'
  let win = await Win.createWindow(config)
  await win.setTitle('这是一个新窗口')
}
let centerWindow = async () => {
  await win.center()
}
</script>
<template>
  <div class="demoBtn" @click="windowSizeChange">改变窗口大小到960*800</div>
  <div class="demoBtn" @click="hideShowWindow">窗口隐藏，3秒钟之后窗口再显示</div>
  <div class="demoBtn" @click="maximizeWindow">最大化窗口</div>
  <div class="demoBtn" @click="restoreWindow">还原窗口</div>
  <div class="demoBtn" @click="minimizeWindow">最小化窗口</div>
  <div class="demoBtn" @click="closeWindow">关闭窗口</div>
  <div class="demoBtn" @click="openWindow">打开一个新窗口</div>
  <div class="demoBtn" @click="centerWindow">移动窗口到屏幕中央</div>
</template>
<style lang="scss" scoped></style>
