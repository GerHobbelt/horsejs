<script setup lang="ts">
import { onMounted, ref } from "vue";
import { app, Win, WindowConfig } from "../../jslib/src/client";
let version = ref("");
let openDemoWindow = async () => {
  let config = new WindowConfig();
  config.title = "第二个窗口";
  config.frameless = true;
  config.url = "http://127.0.0.1:5173/";
  await Win.createWindow(config);
};
let openDocBrowser = () => {};
onMounted(async () => {
  let versionInfo = await app.getVersionInfo();
  version.value = versionInfo.horseJsVersion.join(".");
});
</script>
<template>
  <div class="content">
    <div class="title">HorseJs</div>
    <div class="version">{{ version }}</div>
    <div class="link">
      <a href="/demo/window">demo</a>
      <a @click="openDocBrowser">doc</a>
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
  a {
    display: block;
    margin: 0px 12px;
    cursor: pointer;
    color: rgb(0, 122, 204);
    text-decoration: none;
  }
  a:hover {
    text-decoration: underline;
  }
}
</style>
