import {
  horse,
  Window,
  WindowConfig,
  WindowMultiViewsConfig,
  ViewOverlayConfig,
  ViewOverlayDockMode,
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
  win.addListener("windowCreated", () => {
    console.log("windowCreated");
  });
  console.log(win);
  let viewOverlayConfig = new ViewOverlayConfig();
  viewOverlayConfig.url = "https://cn.bing.com";
  viewOverlayConfig.dock = true;
  viewOverlayConfig.top = 10;
  viewOverlayConfig.left = 10;
  viewOverlayConfig.bottom = 10;
  viewOverlayConfig.right = 10;
  viewOverlayConfig.width = 400;
  viewOverlayConfig.height = 400;
  setTimeout(async () => {
    await win.addViewOverlay(viewOverlayConfig);
  }, 6000);
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
