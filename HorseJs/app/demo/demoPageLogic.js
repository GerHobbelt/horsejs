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
  },
};
