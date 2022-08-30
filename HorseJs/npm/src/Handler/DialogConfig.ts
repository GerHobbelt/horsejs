export class DialogConfig {
  title?: string
  defaultPath?: string
  multiSelections: boolean = true
  filters?: string[] = ['*']
  filterIndex?: number = 0
}
