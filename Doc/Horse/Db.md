HorseJs 内置了客户端数据库支持，使用的是 SQLite 数据库.

# 打开（创建）数据库

整个应用共享一个数据库连接，也就是说开发者在任何一个窗口打开了数据库，在其他窗口都可以操作数据库

```js
let result = await horse.db.open();
```

# 关闭数据库

```js
let result = await horse.db.close();
```

# 执行 SQL 指令

可以一次性执行多条 sql 语句，sql 语句之间用分号隔开

```js
let result = await horse.db.execute({
  sql: `CREATE TABLE Message(Message TEXT NOT NULL, fromUser CHAR(60) NOT NULL, toUser CHAR(60)  NOT NULL, sendTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP);`,
});
result = await horse.db.execute({
  sql: `select rowid,* from  Message where rowid = 88 or rowid = 65;`,
});
result = await horse.db.execute({
  sql: `delete from  Message where rowid = 14;`,
});
let obj = {
  message:
    "怒发冲冠，凭栏处、潇潇雨歇。抬望眼、仰天长啸，壮怀激烈。三十功名尘与土，八千里路云和月。莫等闲、白了少年头，空悲切。 靖康耻，犹未雪。臣子恨，何时灭。驾长车，踏破贺兰山缺。壮志饥餐胡虏肉，笑谈渴饮匈奴血。待从头、收拾旧山河，朝天阙。",
  fromUser: "岳飞",
  toUser: "辛弃疾",
};
result = await horse.db.execute({
  sql: `update Message set Message = '${obj.message}',fromUser = '${obj.fromUser}',toUser='${obj.toUser}' where rowid = 16;`,
});
```
