let esbuild = require("esbuild");
esbuild
  .build({
    entryPoints: ["./src/index.ts"],
    outfile: "./debug/index.js",
    bundle: true,
    watch: true,
    platform: "node",
    minify: false,
    sourcemap: true,
    inject: ["./scripts/debug.env.js"],
  })
  .then((result) => {
    require("../debug/index.js");
  });
