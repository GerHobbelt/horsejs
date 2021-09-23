//防抖
let debounce = (fn, span = 680) => {
  let timer = null;
  return function () {
    clearTimeout(timer);
    timer = setTimeout(() => fn.apply(this, arguments), span);
  };
};
//限流
let throttle = (fn, span = 680) => {
  let timer = null;
  return function () {
    if (timer) return;
    timer = setTimeout(() => {
      fn.apply(this, arguments);
      timer = null;
    }, span);
  };
};
window.addEventListener("load", () => {
  let btnArr = document.querySelector(".titleTool").children;
  btnArr[0].addEventListener("click", () => {
    horse.window.minimize();
  });
  btnArr[1].addEventListener("click", () => {
    if (btnArr[1].classList.contains("horse-restore")) {
      horse.window.restore();
    } else {
      horse.window.maximize();
    }
  });
  btnArr[2].addEventListener("click", () => {
    horse.window.close();
  });
  let maximizeLogic = () => {
    if (
      window.outerHeight === screen.availHeight &&
      window.outerWidth === screen.availWidth
    ) {
      btnArr[1].classList.remove("horse-maximize");
      btnArr[1].classList.add("horse-restore");
    } else {
      btnArr[1].classList.remove("horse-restore");
      btnArr[1].classList.add("horse-maximize");
    }
  };
  maximizeLogic();
  window.addEventListener("resize", debounce(maximizeLogic));
  horse.dialog.openFile({
    title: "test",
    defaultFilePath: "C:\\AMD",
    filters: ["*"],
    lastFilterIndex: 0,
  });
});
