export class BaseWindowConfig {
  /**
   * 是否显示窗口
   */
  show = true
  /**
   * 窗口标题栏的标题
   */
  title: string
  /**
   * 窗口宽度，默认值800
   */
  width = 800
  /**
   * 窗口高度，默认值600
   */
  height = 600
  /**
   * 窗口位置x，默认值100
   * 设置position为center后，窗口位置x,y无效
   */
  x = 100
  /**
   * 窗口位置y，默认值100
   * 设置position为center后，窗口位置x,y无效
   */
  y = 100
  /**
   *  窗口位置，默认值center
   * 值为center时，窗口出现在屏幕中央,窗口位置x,y无效
   * 值为absolute时，窗口使用x,y配置项确定位置
   */
  position: 'center' | 'absolute' = 'center'
  /**
   * 是否为无边框窗口，默认值false
   */
  frameless = false
}
