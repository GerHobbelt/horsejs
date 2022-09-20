<script setup lang="ts">
import { onMounted, ref, onUnmounted } from "vue";
import { horse, Win } from "../../../jslib/src/client";
let props = defineProps<{ title?: string }>();
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
  win.setTitle(props.title as string);
});
onUnmounted(() => {
  win.off("unMaximized", unmaximizeEvent);
  win.off("maximized", maximizeEvent);
});
</script>
<template>
  <div class="topBar">
    <div class="titleLogo">
      <img src="../assets/logo.png" />
    </div>
    <div class="titleText">{{ title }}</div>
    <div class="titleTool">
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
  -webkit-app-region: drag;
  width: 100%;
  height: 38px;
  line-height: 38px;
  background-color: rgb(60, 60, 60);
}
.titleLogo {
  width: 38px;
  display: flex;
  justify-content: center;
  align-items: center;
}
.titleLogo img {
  width: 18px;
  height: 18px;
}
.titleText {
  height: 38px;
  line-height: 38px;
  font-size: 13px;
  color: rgb(206, 206, 206);
  flex: 1;
}
.titleTool {
  -webkit-app-region: no-drag;
  height: 38px;
  float: right;
  color: white;
  line-height: 38px;
  display: flex;
  justify-content: flex-end;
}
.titleTool div {
  text-align: center;
  width: 42px;
  height: 38px;
  color: rgb(206, 206, 206);
  i {
    font-size: 12px;
  }
}
.titleTool div:hover {
  background-color: rgb(80, 80, 80);
}
.titleTool div:last-child:hover {
  background-color: rgba(214, 20, 37, 0.6) !important;
}
</style>
