import EventEmitter from 'eventemitter3';
class Dialog extends EventEmitter {
  showOpenFolderDialog() {}
  showOpenFileDialog() {}
  showSaveFileDialog() {}
  showMessageDialog() {}
  showErrorDialog() {}
}
export let dialog = new Dialog();
