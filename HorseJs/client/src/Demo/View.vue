<script lang="ts" setup>
import { View } from '../../../jslib/src/client'
let getUrl = async () => {
  await getUrl()
}
</script>
<template>
  <div class="demoBtn" @click="getUrl">获取Url</div>
  <div class="demoBtn">打开文件（允许选择多个文件）</div>
  <div class="demoBtn">打开一个目录</div>
</template>
