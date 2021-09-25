let esbuild = require("esbuild");
let path = require("path");
let fs = require("fs");
let os = require("os");
let entryFilePath = path.join(process.cwd(), "main.ts");
let outfile = path.join(process.cwd(), "extension.js");
esbuild.buildSync({
  entryPoints: [entryFilePath],
  outfile,
  minify: false,
  bundle: true,
  sourcemap: false,
});
// let js = `native function __horseFunc();${os.EOL}${fs.readFileSync(outfile)}`;
// fs.writeFileSync(outfile, js);
