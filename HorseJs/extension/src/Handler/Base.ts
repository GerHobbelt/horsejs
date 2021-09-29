import { Util } from '../Util'

export class Base {
  getFirstArgument(method) {
    return `${(<any>this).constructor.name}_${method.name}_${Util.randomNum()}`
  }
}
