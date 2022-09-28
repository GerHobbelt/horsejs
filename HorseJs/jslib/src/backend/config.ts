export class Config {
  version = '0.0.1';
  productName = 'HorseJs';
  productClass = 'horsejs.com';
  httpAndWebSocketServicePort = '1234';
  chromeSwitch = [];
  constructor() {
    console.log(this.version);
  }
}
export let config = new Config();
