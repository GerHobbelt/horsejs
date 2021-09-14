export let demoPageLogic = {
  init: () => {
    document.querySelector("#menuContainer").addEventListener("click", (e) => {
      console.log(e);
    });
  },
};
