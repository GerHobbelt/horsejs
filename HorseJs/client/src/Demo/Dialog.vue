<script lang="ts" setup>
import { dialog } from '../../../jslib/src/client'
let showOpenFileDialog = async () => {
  await dialog.showOpenFileDialog()
}
</script>
<template>
  <div class="demoBtn" @click="showOpenFileDialog">打开文件（只能选择一个文件）</div>
  <div class="demoBtn">打开文件（允许选择多个文件）</div>
  <div class="demoBtn">打开一个目录</div>
</template>
