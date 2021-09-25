export class Window {
  private getFirstArgument(method: Function) {
    return `${Window.name}_${method.name}`;
  }
  maximize() {
    let arg = this.getFirstArgument(this.maximize);
    // @ts-ignore
    __horseFunc(arg);
  }
  minimize() {
    let arg = this.getFirstArgument(this.minimize);
    // @ts-ignore
    return __horseFunc(arg);
  }
  close() {
    let arg = this.getFirstArgument(this.close);
    // @ts-ignore
    __horseFunc(arg);
  }
  restore() {
    let arg = this.getFirstArgument(this.restore);
    // @ts-ignore
    __horseFunc(arg);
  }
  hide() {
    let arg = this.getFirstArgument(this.hide);
    // @ts-ignore
    __horseFunc(arg);
  }
  show() {
    let arg = this.getFirstArgument(this.show);
    // @ts-ignore
    __horseFunc(arg);
  }
  resize(width, height) {
    let arg = this.getFirstArgument(this.resize);
    // @ts-ignore
    __horseFunc(arg);
  }
}
