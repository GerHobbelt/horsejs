<script setup lang="ts">
import { onMounted, ref, onUnmounted } from "vue";
import { horse, Win } from "../../../jslib/src/client";
defineProps<{ title?: string }>();
let isMaximized = ref(false);
let win: Win;
let close = async () => {
  await win.close();
};
let maxmize = async () => {
  await win.maximize();
};
let minimize = async () => {
  await win.minimize();
};
let restore = async () => {
  await win.restore();
};
let maximizeEvent = () => {
  isMaximized.value = true;
};
let unmaximizeEvent = () => {
  isMaximized.value = false;
};

onMounted(async () => {
  win = await Win.getCurrentWindow();
  win.on("unMaximized", unmaximizeEvent);
  win.on("maximized", maximizeEvent);
  isMaximized.value = win.getIsMaximized();
});
onUnmounted(() => {
  win.off("unMaximized", unmaximizeEvent);
  win.off("maximized", maximizeEvent);
});
</script>
<template>
  <div class="topBar">
    <div class="winTitle">{{ title }}</div>
    <div class="winTool">
      <div @click="minimize">
        <i class="icon icon-minimize" />
      </div>
      <div v-if="isMaximized" @click="restore">
        <i class="icon icon-restore" />
      </div>
      <div v-else @click="maxmize">
        <i class="icon icon-maximize" />
      </div>
      <div @click="close">
        <i class="icon icon-close" />
      </div>
    </div>
  </div>
</template>
<style scoped lang="scss">
.topBar {
  display: flex;
  height: 25px;
  line-height: 25px;
  -webkit-app-region: drag;
  width: 100%;
}
.winTitle {
  flex: 1;
  padding-left: 12px;
  font-size: 14px;
  color: #888;
}
.winTool {
  height: 100%;
  display: flex;
  -webkit-app-region: no-drag;
}
.winTool div {
  height: 100%;
  width: 34px;
  text-align: center;
  color: #999;
  cursor: pointer;
  line-height: 25px;
}
.winTool .icon {
  font-size: 10px;
  color: #666666;
  font-weight: bold;
}
.winTool div:hover {
  background: #efefef;
}
.winTool div:last-child:hover {
  background: #ff7875;
}
.winTool div:last-child:hover i {
  color: #fff !important;
}
</style>
