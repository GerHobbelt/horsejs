export let titleBarBtnLogic = () => {
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
  horse.window.addEventListener("maximize", () => {
    btnArr[1].classList.remove("horse-maximize");
    btnArr[1].classList.add("horse-restore");
  });
  horse.window.addEventListener("unMaximize", () => {
    btnArr[1].classList.remove("horse-restore");
    btnArr[1].classList.add("horse-maximize");
  });
};
