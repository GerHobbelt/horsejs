export class BrowserViewConfig {
  /**
   * view地址
   */
  url: string
  /**
   * 停靠信息
   * type为0时，a为left,b为top,c为width,d为height，view大小不随窗口变化而变化
   * type为1时，a为left,b为top,c为right,d为height，view宽度随窗口变化而变化
   * type为2时，a为left,b为top,c为bottom,d为width，view高度随窗口变化而变化
   *
   * type为3时，a为right,b为bottom,c为width,d为height，view大小不随窗口变化而变化
   * type为4时，a为right,b为bottom,c为top,d为width，view高度随窗口变化而变化
   * type为5时，a为right,b为bottom,c为left,d为height，view高度随窗口变化而变化、
   *
   * type为6时，a为left,b为top,c为right,d为bottom，view大小随窗口变化而变化
   */
  dockType: 0 | 1 | 2 | 3 | 4 | 5 | 6
  a: number
  b: number
  c: number
  d: number
}
