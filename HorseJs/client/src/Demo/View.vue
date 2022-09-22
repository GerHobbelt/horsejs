<script lang="ts" setup>
import { View } from '../../../jslib/src/client'
let showOpenFileDialog = async (multiSelection: boolean) => {
  let view = View.getCurrentView()
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
  let view = View.getCurrentView()
  let obj = await view.showOpenFolderDialog({
    title: '打开文件!!',
    defaultPath: 'C:\\Windows',
  })
  alert(obj)
}
let showSaveFileDialog = async () => {
  let view = View.getCurrentView()
  let obj = await view.showSaveFileDialog({
    title: '保存文件!!',
    defaultPath: 'C:\\Windows',
  })
  alert(obj)
}
</script>
<template>
  <div class="demoBtn" @click="showOpenFileDialog(false)">打开文件（只能选择一个文件）</div>
  <div class="demoBtn" @click="showOpenFileDialog(true)">打开文件（允许选择多个文件）</div>
  <div class="demoBtn" @click="showOpenFolderDialog()">打开一个目录</div>
  <div class="demoBtn" @click="showSaveFileDialog()">保存文件</div>
</template>
