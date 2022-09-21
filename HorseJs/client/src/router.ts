import * as VueRouter from 'vue-router'
//路由规则描述数组
const routes = [
  { path: '/', redirect: '/main' },
  {
    path: '/main',
    component: () => import('./Main.vue'),
  },
  {
    path: '/demo',
    component: () => import('./Demo.vue'),
    children: [
      {
        path: 'window',
        component: () => import('./Demo/Window.vue'),
      },
      {
        path: 'view',
        component: () => import('./Demo/View.vue'),
      },
      {
        path: 'dialog',
        component: () => import('./Demo/Dialog.vue'),
      },
    ],
  },
]
//导出路由对象
export let router = VueRouter.createRouter({
  history: VueRouter.createWebHistory(),
  routes,
})
