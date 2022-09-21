import { BaseView } from '../common/BaseView';
export class View extends BaseView {
  private static currentView: View;
  private static mainView: View;
  /**
   * 获取当前View
   * @returns
   */
  static getCurrentView(): View {
    if (globalThis.__mainViewId === globalThis.__curViewId) {
      return this.getMainView();
    } else {
      if (this.currentView) return this.currentView;
      this.currentView = new View(globalThis.__curViewId);
      return this.currentView;
    }
  }
  /**
   * 获取当前窗口主View
   * @returns
   */
  static getMainView(): View {
    if (this.mainView) return this.mainView;
    this.mainView = new View(globalThis.__mainViewId);
    return this.mainView;
  }
}
