<script lang="ts" setup>
import { ref, watch } from 'vue'
import { useRoute } from 'vue-router'
let route = useRoute()
let menus = ref([
  {
    path: `/demo/window`,
    title: '窗口',
    isSelected: true,
  },
  {
    path: `/demo/dialog`,
    title: '对话框',
    isSelected: false,
  },
  {
    path: `/demo/dialog`,
    title: '对话框',
    isSelected: false,
  },
])
watch(
  () => route,
  () => menus.value.forEach((v) => (v.isSelected = v.path === route.fullPath)),
  {
    immediate: true,
    deep: true,
  }
)
</script>
<template>
  <div class="demo">
    <div id="menuContainer">
      <router-link v-for="item in menus" :to="item.path" :class="[``, { menuSelected: item.isSelected }]">{{ item.title }}</router-link>
    </div>
    <div class="demoBox">
      <router-view />
    </div>
  </div>
</template>
<style lang="scss" scoped>
.demo {
  color: #333;
  background: #fff;
  flex: 1;
  display: flex;
}
#menuContainer {
  background: rgb(219, 237, 255);
  width: 180px;
  line-height: 38px;
  font-size: 15px;
  padding: 12px 0px;
}
#menuContainer a {
  cursor: pointer;
  padding-left: 16px;
  border-left: 6px solid transparent;
  display: block;
  text-decoration: none;
  padding-left: 16px;
  color: #333;
}
#menuContainer a:hover {
  background: rgb(140, 200, 255);
  color: #fff;
  border-left: 6px solid rgb(121, 184, 255);
}

#menuContainer .menuSelected {
  background: rgb(33, 136, 255) !important;
  color: #fff;
  border-left: 6px solid rgb(0, 92, 197) !important;
  position: relative;
}
#menuContainer .menuSelected::after {
  display: block;
  width: 0px;
  height: 0px;
  position: absolute;
  right: 0px;
  top: calc(50% - 4px);
  border-top: solid 4px transparent;
  border-right: solid 4px #fff;
  border-bottom: solid 4px transparent;
  content: '';
}
#demoContainer {
  flex: 1;
  display: flex;
  flex-direction: column;
  overflow: hidden;
}
.demoBox {
  padding: 26px;
  overflow-y: auto;
  flex: 1;
}
</style>
