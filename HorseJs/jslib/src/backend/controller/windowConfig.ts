export class WindowConfig {
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
  /**
   * 窗口布局，默认值fill
   * 当窗口布局为fill时，一个窗口只能添加一个view
   */
  layout: 'fill' | 'box' = 'fill'
  /**
   * 窗口布局为box时，此参数确定布局方向，默认值horizontal
   */
  layoutDirection: 'horizontal' | 'vertical' = 'horizontal'
  /**
   * 页面数组
   * url为页面地址
   * flex弹性值，当layout为box时，此值有效，必须是正整数
   */
  views: {
    url: string
    flex: number
  }[]
  constructor() {}
}
