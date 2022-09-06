import { horse, Window, WindowConfig, ViewConfig } from "../../jslib/src/backend";
import { config } from "../horse.config";

let createWindow = async () => {
  let config = new WindowConfig();
  config.title = "这是我的窗口！！！";
  config.frameless = true;
  config.url = "https://www.baidu.com";
  let win: Window = await Window.createWindow(config);
  // let config2 = new WindowConfig();
  // config2.position = "absolute";
  // config2.title = "这是我的窗口！！！";
  // config2.frameless = true;
  // config2.url = "https://www.baidu.com";
  // let win2: Window = await Window.createWindow(config2);
  // setTimeout(async () => {
  //   await win.hide();
  //   console.log("hide window");
  //   setTimeout(async () => {
  //     await win.show();
  //     console.log("show window");
  //   }, 3000);
  // }, 8000);

  // console.log(win);

  let viewConfig = new ViewConfig();
  viewConfig.url = "https://cn.bing.com";
  viewConfig.dockType = 0;
  viewConfig.a = 20;
  viewConfig.b = 20;
  viewConfig.c = 400;
  viewConfig.d = 400;
  let view = await win.addView(viewConfig);
  console.log(view.id);

  setTimeout(() => {
    win.removeView(view);
  }, 6000);

  // setTimeout(async () => {
  //   let viewConfig2 = new ViewConfig();
  //   viewConfig2.url = "https://www.so.com";
  //   viewConfig2.dockType = 0;
  //   viewConfig2.a = 12;
  //   viewConfig2.b = 12;
  //   viewConfig2.c = 300;
  //   viewConfig2.d = 300;
  //   let view2 = await win.addView(viewConfig2);
  //   console.log(view2.id);
  // }, 18000);
  // console.log("ok");

  // setTimeout(() => {
  //   win.view.openDevTools();
  //   setTimeout(() => {
  //     win.view.closeDevTools();
  //   }, 6000);
  // }, 6000);
};

horse.addListener("serviceReady", (app) => {
  app.use((ctx) => {
    ctx.body = "Hello Koa";
  });
});

horse.addListener("browserReady", () => {
  // createWindowOverlayView();
  // createWindowMultiView();
  createWindow();
});
horse.init(config);
