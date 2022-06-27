export let processor = {
  openDb: async () => {
    let result = await horse.db.open();
    console.log(result);
  },
  closeDb: async () => {
    let result = await horse.db.close();
    console.log(result);
  },
  excute: async () => {
    let result = await horse.db.excute();
    console.log(result);
  },
};
