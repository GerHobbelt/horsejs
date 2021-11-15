let esbuild = require('esbuild')
let path = require('path')
let build = (src, dest) => {
  esbuild.buildSync({
    entryPoints: [src],
    outfile: dest,
    minify: process.argv.includes('--minify'),
    bundle: true,
    sourcemap: false,
    platform: 'neutral',
  })
}
build(path.join(__dirname, 'src/main.ts'), path.join(__dirname, 'dist/horse.js'))
build(path.join(__dirname, 'app/index.ts'), path.join(__dirname, 'app/index.js'))
build(path.join(__dirname, 'app/demo.ts'), path.join(__dirname, 'app/demo.js'))
let now = new Date()
console.log('-------------------------------------')
console.log(`build extension ok  ${now.getHours()}:${now.getMinutes()}:${now.getSeconds()}`)
console.log('-------------------------------------')
