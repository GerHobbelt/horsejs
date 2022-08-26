import { horse } from "../../jslib/src/backend";
import { config } from "../horse.config";
horse.onServiceReady = (app) => {
  app.use((ctx) => {
    ctx.body = "Hello Koa";
  });
};
horse.onBrowserReady = () => {
  horse.window.createWindow({
    with: 800,
    height: 600,
    x: 100,
    y: 100,
  });
};
horse.init(config);
