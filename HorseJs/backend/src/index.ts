import { horse } from "../../jslib/src/backend";
let app = horse.init();
app.use((ctx) => {
  ctx.body = "Hello Koa";
});
