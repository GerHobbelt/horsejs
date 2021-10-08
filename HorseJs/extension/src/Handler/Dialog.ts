import { Util } from "../Util";

export class Dialog {
  private getFirstArgument(method: Function) {
    return `${Dialog.name}_${method.name}_${Util.randomNum()}`;
  }
  openFile({ title, defaultFilePath, filters, lastFilterIndex }) {
    let arg = this.getFirstArgument(this.openFile);
    // @ts-ignore
    __horseFunc(arg, title, defaultFilePath, filters, lastFilterIndex);
  }
  openFolder({ title, defaultFilePath, filters, lastFilterIndex }) {
    let arg = this.getFirstArgument(this.openFolder);
    // @ts-ignore
    __horseFunc(arg, title, defaultFilePath, filters, lastFilterIndex);
  }
}
