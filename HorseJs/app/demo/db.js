export let processor = {
  openDb: async () => {
    let result = await horse.db.open();
    console.log(result);
  },
  closeDb: async () => {
    let result = await horse.db.close();
    console.log(result);
  },
  createTable: async () => {
    let result = await horse.db.execute({
      sql: `CREATE TABLE Message(id INT PRIMARY KEY NOT NULL, Message TEXT NOT NULL, fromUser CHAR(60) NOT NULL, toUser CHAR(60)  NOT NULL, sendTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP);`,
      onData: (data) => {
        console.log("dbOnData:", data);
      },
    });
    console.log(result);
  },
  insertData: async () => {
      
    let result = await horse.db.execute({
      sql: `CREATE TABLE Message(id INT PRIMARY KEY NOT NULL, Message TEXT NOT NULL, fromUser CHAR(60) NOT NULL, toUser CHAR(60)  NOT NULL, sendTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP);`,
      onData: (data) => {
        console.log("dbOnData:", data);
      },
    });
    console.log(result);
  },
};
