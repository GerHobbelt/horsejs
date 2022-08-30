import { BaseWindowConfig } from './BaseWindowConfig'
export enum WindowOverlayDockMode {
  topLeft = 1,
  topRight,
  bottomLeft,
  bottomRight,
  custom,
}
export class WindowOverlayViewConfig extends BaseWindowConfig {
  views: { url: string; dockMode: WindowOverlayDockMode }[]
}
