let $ = (selector) => document.querySelector(selector);
export let demoPageLogic = {
  init: () => {
    $("#menuContainer").addEventListener("click", (e) => {
      let id = e.target.getAttribute("id");
      if (!id || e.target.classList.contains("menuSelected")) return;
      $(".menuSelected").classList.remove("menuSelected");
      e.target.classList.add("menuSelected");
      $(".sectionSelected").classList.remove("sectionSelected");
      $(`#${id.replace("menu", "section")}`).classList.add("sectionSelected");
    });
    $(".sectionCodeLink").addEventListener("click", () => {
      let codeFileName = $(".menuSelected")
        .getAttribute("id")
        .replace("menu", "")
        .toLowerCase();
      let target = `https://gitee.com/horsejs/horsejs/blob/master/HorseJs/app/demo/${codeFileName}.js`;
      horse.shell.openExternal({ target, workingDir: "" });
    });
    $("#demoContainer").addEventListener("click", async (e) => {
      if (!e.target.classList.contains("demoBtn")) return;
      let id = e.target.getAttribute("id");
      let parentId = e.target.parentElement.getAttribute("id");
      parentId = parentId.replace("section", "").toLowerCase();
      let { processor } = await import(`./${parentId}.js`);
      processor[id]();
    });
  },
};
