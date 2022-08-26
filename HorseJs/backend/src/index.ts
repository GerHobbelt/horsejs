import { horse } from "../../jslib/src/backend";
import { config } from "../horse.config";
horse.onServiceReady = (app) => {
  app.use((ctx) => {
    ctx.body = "Hello Koa";
  });
};
horse.init(config);
