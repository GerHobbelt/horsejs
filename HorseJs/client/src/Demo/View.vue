<script lang="ts" setup>
import { View } from '../../../jslib/src/client'
let view = View.getCurrentView()
let showOpenFileDialog = async (multiSelection: boolean) => {
  let obj = await view.showOpenFileDialog({
    title: '打开文件!!',
    defaultPath: 'C:\\Windows',
    multiSelection,
  })
  if (typeof obj === 'string') {
    alert(obj)
  } else {
    alert(obj.join(','))
  }
}
let showOpenFolderDialog = async () => {
  let obj = await view.showOpenFolderDialog({
    title: '打开文件!!',
    defaultPath: 'C:\\Windows',
  })
  alert(obj)
}
let showSaveFileDialog = async () => {
  let obj = await view.showSaveFileDialog({
    title: '保存文件!!',
    defaultPath: 'C:\\Windows',
  })
  alert(obj)
}
let openDevTool = async () => {
  await view.openDevTools()
}
let closeDevTool = async () => {
  await view.closeDevTools()
}
</script>
<template>
  <div class="demoBtn" @click="showOpenFileDialog(false)">打开文件对话框（只能选择一个文件）</div>
  <div class="demoBtn" @click="showOpenFileDialog(true)">打开文件对话框（允许选择多个文件）</div>
  <div class="demoBtn" @click="showOpenFolderDialog">打开目录对话框</div>
  <div class="demoBtn" @click="showSaveFileDialog">保存文件对话框</div>
  <div class="demoBtn" @click="openDevTool">打开调试器窗口</div>
  <div class="demoBtn" @click="closeDevTool">关闭调试器窗口</div>
</template>
