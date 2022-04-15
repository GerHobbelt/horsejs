let esbuild = require('esbuild')
let path = require('path')
let fs = require('fs')
let os = require('os')
let entryFilePath = path.join(__dirname, 'main.ts')
let outfile = path.join(__dirname, '../extension.js')
esbuild.buildSync({
  entryPoints: [entryFilePath],
  outfile,
  minify: process.argv.includes('--minify'),
  bundle: true,
  sourcemap: false,
})
let pre = `var horse;` //native function __callHorseFunc();${os.EOL}
let js = `${pre}${os.EOL}${fs.readFileSync(outfile)}`
fs.writeFileSync(outfile, js)
let now = new Date()
console.log('-------------------------------------')
console.log(outfile)
console.log(`build extension ok  ${now.getHours()}:${now.getMinutes()}:${now.getSeconds()}`)
console.log('-------------------------------------')
