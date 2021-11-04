export let processor = {
  initSqlite: async () => {
    let result = await horse.plugin.load({
      name: "HorseSqlite",
      async: false,
      paramObject: {
        openWhenLoad: true,
        dbFileAtAppDataFolder: true,
        dbFileName: "db.db",
        dbFolderPath: "",
      },
    });
    console.log("Load HorseSqlite", result);
  },
  createTable: async () => {
    let result = await horse.plugin.excute({
      name: "HorseSqlite",
      async: false,
      paramObject: {
        sql: `CREATE TABLE Message(id INT PRIMARY KEY NOT NULL, Message TEXT NOT NULL, fromUser CHAR(60) NOT NULL, toUser CHAR(60)  NOT NULL, sendTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP);`,
      },
    });
    console.log("HorseSqlite result", result);
  },
  unload: async () => {
    let result = await horse.plugin.unload();
    console.log(result);
  },
};
