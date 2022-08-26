import { horse } from "../../jslib/src/backend";
horse.onServiceReady = (app) => {
  app.use((ctx) => {
    ctx.body = "Hello Koa";
  });
};
horse.init();
