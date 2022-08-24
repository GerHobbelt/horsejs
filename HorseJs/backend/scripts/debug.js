let esbuild = require("esbuild");
esbuild
  .build({
    entryPoints: ["./src/index.ts"],
    outfile: "../../x64/debug/backend/index.js",
    bundle: true,
    watch: true,
    platform: "node",
    minify: false,
    sourcemap: true,
    inject: ["./scripts/debug.env.js"],
  })
  .then((result) => {
    require("../../../x64/debug/backend/index.js");
  });
