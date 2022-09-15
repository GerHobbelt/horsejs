import { horse, Window, WindowConfig, ViewConfig } from "../../jslib/src/backend";
import { config } from "../horse.config";

let createWindow = async () => {
  let config = new WindowConfig();
  config.title = "这是我的窗口！！！";
  config.frameless = true;
  config.url = "https://www.baidu.com";
  let win: Window = await Window.createWindow(config);
  return win;
};
let x = 0;
let y = 0;
let createView = async (win: Window) => {
  let viewConfig = new ViewConfig();
  viewConfig.url = "https://cn.bing.com";
  viewConfig.dockType = 0;
  viewConfig.a = x;
  viewConfig.b = y;
  viewConfig.c = 400;
  viewConfig.d = 400;
  let view = await win.addView(viewConfig);
  x += 30;
  y += 30;
  return view;
};

horse.addListener("serviceReady", (app) => {
  app.use((ctx) => {
    ctx.body = "Hello Koa";
  });
});

horse.addListener("browserReady", async () => {
  // createWindowOverlayView();
  // createWindowMultiView();
  x = 0;
  y = 0;
  let win = await createWindow();
  let view = await createView(win);
  // let view2 = await createView(win);
  // let view3 = await createView(win);
  // setTimeout(() => {
  //   win.removeView(view);
  // }, 8000);
});
horse.init(config);
