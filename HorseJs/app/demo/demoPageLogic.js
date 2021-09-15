export let demoPageLogic = {
  init: () => {
    let menuContainer = document.querySelector("#menuContainer");
    menuContainer.addEventListener("click", (e) => {
      if (e.target == menuContainer) return;
      if (e.target.classList.contains("menuSelected")) return;
      document.querySelector(".menuSelected").classList.remove("menuSelected");
      e.target.classList.add("menuSelected");
      let id = e.target.getAttribute("id").replace("menu", "section");
      document
        .querySelector(".sectionSelected")
        .classList.remove("sectionSelected");
      document.querySelector(`#${id}`).classList.add("sectionSelected");
    });
    document.querySelector(".sectionCodeLink").addEventListener("click", () => {
      let codeFileName = document
        .querySelector(".menuSelected")
        .getAttribute("id")
        .replace("menu", "")
        .toLowerCase();
      let target = `https://gitee.com/horsejs/horsejs/blob/master/HorseJs/app/demo/${codeFileName}.js`;
      horse.shell.openExternal({ target, workingDir: "" });
    });
  },
};
