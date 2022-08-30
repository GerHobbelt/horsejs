import { horse } from '../../src/main'
export class Db {
  static className = 'Db'
  async openDb() {
    let result = await horse.db.open()
    console.log(result)
  }
  async closeDb() {
    let result = await horse.db.close()
    console.log(result)
  }
  async createTable() {
    let result = await horse.db.execute({
      sql: `CREATE TABLE Message(Message TEXT NOT NULL, fromUser CHAR(60) NOT NULL, toUser CHAR(60)  NOT NULL, sendTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP);`,
    })
    console.log(result)
  }
  async insertData() {
    let sqls = []
    let msgs = [
      {
        message: `天接云涛连晓雾，星河欲转千帆舞。仿佛梦魂归帝所。闻天语，殷勤问我归何处。 我报路长嗟日暮，学诗谩有惊人句。九万里风鹏正举。风休住，蓬舟吹取三山去！`,
        fromUser: `李清照`,
        toUser: '辛弃疾',
      },
      {
        message: `醉里挑灯看剑，梦回吹角连营。八百里分麾下炙，五十弦翻塞外声。沙场秋点兵。 马作的卢飞快，弓如霹雳弦惊。了却君王天下事，赢得生前身后名。可怜白发生！`,
        fromUser: `辛弃疾`,
        toUser: '李清照',
      },
    ]
    for (let i = 0; i < 100; i++) {
      let msg = msgs[i % 2]
      sqls.push(`insert into Message(Message, fromUser, toUser) values ('${msg.message}','${msg.fromUser}','${msg.toUser}');`)
    }
    let result = await horse.db.execute({
      sql: sqls.join(''),
    })
    console.log(result)
  }
  async selectData() {
    let result = await horse.db.execute({
      sql: `select rowid,* from  Message where rowid = 88 or rowid = 65;`,
    })
    console.log(result)
  }
  async deleteData() {
    let result = await horse.db.execute({
      sql: `delete from  Message where rowid = 14;`,
    })
    console.log(result)
  }
  async updateData() {
    let obj = {
      message: '怒发冲冠，凭栏处、潇潇雨歇。抬望眼、仰天长啸，壮怀激烈。三十功名尘与土，八千里路云和月。莫等闲、白了少年头，空悲切。 靖康耻，犹未雪。臣子恨，何时灭。驾长车，踏破贺兰山缺。壮志饥餐胡虏肉，笑谈渴饮匈奴血。待从头、收拾旧山河，朝天阙。',
      fromUser: '岳飞',
      toUser: '辛弃疾',
    }
    let result = await horse.db.execute({
      sql: `update Message set Message = '${obj.message}',fromUser = '${obj.fromUser}',toUser='${obj.toUser}' where rowid = 16;`,
    })
    console.log(result)
  }
}
