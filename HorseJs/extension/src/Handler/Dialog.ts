import { Util } from '../Util'
declare let __horseFunc: (msgName: string, ...otherParams) => {}
export class Dialog {
  private getFirstArgument(method: Function) {
    // @ts-ignore
    return `${Dialog.name}_${method.name}_${Util.randomNum()}`
  }
  openFile({ title, defaultFilePath, filters, lastFilterIndex }) {
    let arg = this.getFirstArgument(this.openFile)
    __horseFunc(arg, title, defaultFilePath, filters, lastFilterIndex)
  }
  openFolder({ title, defaultFilePath, filters, lastFilterIndex }) {
    let arg = this.getFirstArgument(this.openFolder)

    __horseFunc(arg, title, defaultFilePath, filters, lastFilterIndex)
  }
}
