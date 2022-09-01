//todo
export enum ViewOverlayDockMode {
  topLeft = 1,
  topRight,
  bottomLeft,
  bottomRight,
  resizeWidth,
  resizeHeight,
  resizeBoth,
}
export class ViewOverlayConfig {
  /**
   * view地址
   */
  url: string
  /**
   * 是否停靠
   */
  dock: boolean
  /**
   * 上边距
   */
  top: number
  /**
   * 左边距
   * dock为true时有效
   */
  left: number
  /**
   * 底边距
   * dock为true时有效
   */
  bottom: number
  /**
   * 右边距
   */
  right: number
  /**
   * 宽度
   * dock为false时有效
   */
  width: number
  /**
   * 高度
   * dock为false时有效
   */
  height: number
}
