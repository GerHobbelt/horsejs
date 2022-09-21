import { horse, Win, WindowConfig, ViewConfig } from "../../jslib/src/backend";
import { config } from "../horse.config";

let createWindow = async () => {
  let config = new WindowConfig();
  config.title = "这是我的窗口！！！";
  config.frameless = true;
  config.url = "http://127.0.0.1:5173/";
  let win: Win = await Win.createWindow(config);
  return win;
};
let x = 0;
let y = 0;
let createView = async (win: Win) => {
  let viewConfig = new ViewConfig();
  viewConfig.url = "https://cn.bing.com";
  viewConfig.dockType = 0;
  viewConfig.a = 10;
  viewConfig.b = 10;
  viewConfig.c = 400;
  viewConfig.d = 400;
  let view = await win.addOverlayView(viewConfig);
  x += 30;
  y += 30;
  return view;
};

let centerAndSize = (win: Win) => {
  setTimeout(async () => {
    await win.center();
    // await win.centerAndSize({ width: 1600, height: 900 });
  }, 8000);
};

let positionAndSize = (win: Win) => {
  setTimeout(async () => {
    // await win.position({ x: 100, y: 100 });
    await win.positionAndSize({ x: 100, y: 100, width: 1600, height: 900 });
  }, 8000);
};

horse.addListener("serviceReady", (app) => {
  app.use((ctx) => {
    ctx.body = "Hello Koa";
  });
});

horse.addListener("browserReady", async () => {
  x = 0;
  y = 0;
  let win = await createWindow();
  setTimeout(async () => {
    let url = await win.view.getUrl();
    console.log(url);
  }, 6000);

  // let bound = await win.getBound();
  // console.log(bound);
  // await positionAndSize(win);
  // await centerAndSize(win);
  // let view2 = await createView(win);
  // let view3 = await createView(win);
  // setTimeout(() => {
  //   win.removeView(view);
  // }, 8000);
});
horse.init(config);
