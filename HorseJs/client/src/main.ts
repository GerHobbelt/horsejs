import { createApp } from "vue";
import "./style.css";
import App from "./App.vue";
import { horse } from "../../jslib/src/client";
horse.init();
createApp(App).mount("#app");
