import { BaseWindowConfig } from './BaseWindowConfig'

export class WindowMultiViewsConfig extends BaseWindowConfig {
  /**
   * 窗口布局为box时，此参数确定布局方向，默认值horizontal
   */
  layoutDirection: 'horizontal' | 'vertical' = 'horizontal'
  /**
   * 页面数组
   * url为页面地址
   * flex弹性值，当layout为box时，此值有效，必须是正整数
   * todo 控制他们的大小
   */
  views: {
    url: string
    flex: number
  }[]
}
