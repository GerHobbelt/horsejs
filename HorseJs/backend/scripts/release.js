let esbuild = require("esbuild");
esbuild.build({
  entryPoints: ["./src/index.ts"],
  outfile: "./release/index.js",
  bundle: true,
  watch: false,
  platform: "node",
  minify: true,
});
