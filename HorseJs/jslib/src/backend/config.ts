export class Config {
  version = '0.0.1';
  productName = 'HorseJs';
  productClass = 'horsejs.com';
  chromeSwitch = [];
  constructor() {
    console.log(this.version);
  }
}
export let config = new Config();
