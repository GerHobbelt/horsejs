import { horse, WindowConfig } from "../../jslib/src/backend";
import { config } from "../horse.config";
horse.onServiceReady = (app) => {
  app.use((ctx) => {
    ctx.body = "Hello Koa";
  });
};
horse.onBrowserReady = () => {
  let config = new WindowConfig();
  config.title = "这是我的窗口！！！";
  config.frameless = false;
  config.layout = "box";
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
  horse.window.createWindow(config);
};
horse.init(config);
