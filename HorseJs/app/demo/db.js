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
      sql: `CREATE TABLE Message(Message TEXT NOT NULL, fromUser CHAR(60) NOT NULL, toUser CHAR(60)  NOT NULL, sendTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP);`,
      onData: (data) => {
        console.log("dbOnData:", data);
      },
    });
    console.log(result);
  },
  insertData: async () => {
    let sqls = [];
    let msgs = [
      {
        message: `天接云涛连晓雾，星河欲转千帆舞。仿佛梦魂归帝所。闻天语，殷勤问我归何处。 我报路长嗟日暮，学诗谩有惊人句。九万里风鹏正举。风休住，蓬舟吹取三山去！`,
        fromUser: `李清照`,
        toUser: "辛弃疾",
      },
      {
        message: `醉里挑灯看剑，梦回吹角连营。八百里分麾下炙，五十弦翻塞外声。沙场秋点兵。 马作的卢飞快，弓如霹雳弦惊。了却君王天下事，赢得生前身后名。可怜白发生！`,
        fromUser: `辛弃疾`,
        toUser: "李清照",
      },
    ];
    for (let i = 0; i < 100; i++) {
      let msg = msgs[i % 2];
      sqls.push(
        `insert into Message(Message, fromUser, toUser) values ('${msg.message}','${msg.fromUser}','${msg.toUser}');`
      );
    }
    let result = await horse.db.execute({
      sql: sqls.join(""),
      onData: (data) => {
        console.log("dbOnData:", data);
      },
    });
    console.log(result);
  },
  selectData: async () => {
    let result = await horse.db.execute({
      sql: `select rowid,* from  Message where rowid = 88 or rowid = 65;`,
      onData: (data) => {
        console.log("dbOnData:", data);
      },
    });
    console.log(result);
  },
};
