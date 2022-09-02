import {
  horse,
  Window,
  WindowConfig,
  WindowMultiViewsConfig,
  BrowserViewConfig,
} from "../../jslib/src/backend";
import { config } from "../horse.config";

// let createWindowMultiView = () => {
//   let config = new WindowMultiViewsConfig();
//   config.title = "这是我的窗口！！！";
//   config.frameless = false;
//   config.layoutDirection = "vertical";
//   config.position = "absolute";
//   config.views = [
//     {
//       url: "https://sso.hikvision.com/login?service=http%3A%2F%2Fsso.hikvision.com.cn%2Fdomino%2FdominoLogin",
//       flex: 3,
//     },
//     {
//       url: "https://sso.hikvision.com/login?service=http%3A%2F%2Fsso.hikvision.com.cn%2Fdomino%2FdominoLogin",
//       flex: 1,
//     },
//   ];
//   horse.window.createWindowMultiView(config);
// };

// let addOverlay = () => {
//   let config = new ViewOverlayConfig();
//   config.url =
//     "https://sso.hikvision.com/login?service=http%3A%2F%2Fsso.hikvision.com.cn%2Fdomino%2FdominoLogin";
//   config.dockMode = ViewOverlayDockMode.topLeft;
//   horse.window.addOverlay(config);
// };

let createWindow = async () => {
  let config = new WindowConfig();
  config.title = "这是我的窗口！！！";
  config.frameless = true;
  config.url = "https://www.baidu.com";
  let win: Window = await Window.createWindow(config);
  let config2 = new WindowConfig();
  config2.position = "absolute";
  config2.title = "这是我的窗口！！！";
  config2.frameless = true;
  config2.url = "https://www.baidu.com";
  let win2: Window = await Window.createWindow(config2);
  setTimeout(async () => {
    await win.hide();
    console.log("hide window");
    setTimeout(async () => {
      await win.show();
      console.log("show window");
    }, 3000);
  }, 8000);

  console.log(win);
  let viewConfig = new BrowserViewConfig();
  viewConfig.url = "https://cn.bing.com";
  viewConfig.dockType = 6;
  viewConfig.a = 120;
  viewConfig.b = 120;
  viewConfig.c = 300;
  viewConfig.d = 300;
  await win.addBrowserView(viewConfig);

  let viewConfig2 = new BrowserViewConfig();
  viewConfig2.url = "https://cn.bing.com";
  viewConfig2.dockType = 0;
  viewConfig2.a = 12;
  viewConfig2.b = 12;
  viewConfig2.c = 300;
  viewConfig2.d = 300;
  await win.addBrowserView(viewConfig2);
  console.log("ok");
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
