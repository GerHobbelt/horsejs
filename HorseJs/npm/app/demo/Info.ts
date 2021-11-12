import { horse } from '../../src/main'
export class Info {
  static className = 'Info'
  async getAppInfo() {
    let result = await horse.info.getAppInfo()
    console.log(result)
  }
  async getHorseInfo() {
    let result = await horse.info.getHorseInfo()
    console.log(result)
  }
  async getOSInfo() {
    let result = await horse.info.getOSInfo()
    console.log(result)
  }
  async getHardwareInfo() {
    let result = await horse.info.getHardwareInfo()
    console.log(result)
  }
  async getNetInfo() {
    let result = await horse.info.getNetInfo()
    console.log(result)
  }
  async getUserInfo() {
    let result = await horse.info.getUserInfo()
    console.log(result)
  }
}
