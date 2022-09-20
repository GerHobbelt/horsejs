<script setup lang="ts">
import { onMounted, ref } from "vue";
import BarTop from "./components/BarTop.vue";
import { app } from "../../jslib/src/client";
let version = ref("");
onMounted(async () => {
  let versionInfo = await app.getVersionInfo();
  version.value = versionInfo.horseJsVersion.join(".");
});
</script>

<template>
  <BarTop title="美好的桌面软件开发!!!"></BarTop>
  <div class="content">
    <div class="title">HorseJs</div>
    <div class="version">{{ version }}</div>
    <div class="link">
      <div id="demoLink">demo</div>
      <div id="docLink">doc</div>
    </div>
  </div>
</template>

<style scoped lang="scss">
.content {
  color: rgb(0, 122, 204);
  flex: 1;
  flex-direction: column;
  text-align: center;
  display: flex;
  align-items: center;
  justify-content: center;
  text-align: justify;
}
.title {
  font-size: 66px;
  padding-bottom: 60px;
}
.version {
  line-height: 32px;
}
.link {
  line-height: 32px;
  display: flex;
}
.link div {
  margin: 0px 12px;
  text-decoration: underline;
  cursor: pointer;
}
</style>
