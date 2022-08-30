import {
  horse,
  WindowConfig,
  WindowMultiViewsConfig,
  WindowOverlayViewConfig,
  WindowOverlayDockMode,
} from "../../jslib/src/backend";
import { config } from "../horse.config";

let createWindowMultiView = () => {
  let config = new WindowMultiViewsConfig();
  config.title = "这是我的窗口！！！";
  config.frameless = false;
  config.layoutDirection = "vertical";
  config.position = "absolute";
  config.views = [
    {
      url: "https://sso.hikvision.com/login?service=http%3A%2F%2Fsso.hikvision.com.cn%2Fdomino%2FdominoLogin",
      flex: 3,
    },
    {
      url: "https://sso.hikvision.com/login?service=http%3A%2F%2Fsso.hikvision.com.cn%2Fdomino%2FdominoLogin",
      flex: 1,
    },
  ];
  horse.window.createWindowMultiView(config);
};

let createWindowOverlayView = () => {
  let config = new WindowOverlayViewConfig();
  config.title = "这是我的窗口！！！";
  config.frameless = false;
  config.position = "absolute";
  config.views = [
    {
      url: "https://sso.hikvision.com/login?service=http%3A%2F%2Fsso.hikvision.com.cn%2Fdomino%2FdominoLogin",
      dockMode: WindowOverlayDockMode.topLeft,
    },
  ];
  horse.window.createWindowOverlayView(config);
};

let createWindow = () => {
  let config = new WindowConfig();
  config.title = "这是我的窗口！！！";
  config.frameless = false;
  config.url =
    "https://sso.hikvision.com/login?service=http%3A%2F%2Fsso.hikvision.com.cn%2Fdomino%2FdominoLogin";
  horse.window.createWindow(config);
};

horse.onServiceReady = (app) => {
  app.use((ctx) => {
    ctx.body = "Hello Koa";
  });
};
horse.onBrowserReady = () => {
  createWindowOverlayView();
  // createWindowMultiView();
  // createWindow();
};
horse.init(config);
