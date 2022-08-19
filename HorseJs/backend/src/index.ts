import Koa from "koa";
import serve from "koa-static";
const app = new Koa();
// process.env.envName
// app.use(serve())
// response
app.use((ctx) => {
  ctx.body = "Hello Koa";
});
let server = app.listen(0, "localhost");
server.on("listening", () => {
  let msg = { name: "backendPort", value: server.address().port, time: 0 };
  console.log(JSON.stringify(msg));
});
