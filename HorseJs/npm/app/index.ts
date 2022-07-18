import { horse } from '../src/main'
import './common'
let linkLogic = () => {
  document.querySelector('#docLink').addEventListener('click', () => {
    horse.system.openExternal({
      target: 'https://gitee.com/horsejs/horsejs#%E6%96%87%E6%A1%A3',
      workingDir: '',
    })
  })
  document.querySelector('#demoLink').addEventListener('click', () => {
    horse.window.open({
      url: 'http://horse/app/demo.html',
      width: 1024,
      height: 768,
    })
  })
}
let setVersion = async () => {
  let data = await horse.info.getHorseInfo()
  let versionNum = data.data.HorseJsVersion.join('.')
  document.querySelector('.version').innerHTML = `version：${versionNum}`
}
window.addEventListener('load', () => {
  linkLogic()
  setVersion()
})
