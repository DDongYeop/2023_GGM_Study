const Sequelize = require('sequelize');
const User = require('./user');
const Comment = require('./comment');

const env = process.env.NODE_ENV || 'development';
const config = require(__dirname + '/../config/config.json')[env];
const db = {};

//config.json에 있는 DB값으로 새로운 시퀄라이즈ㅡ 객체 생성 
const sequelize = new Sequelize(config.database, config.username, config.password, config);

db.sequelize = sequelize;

//테이블과 모델 연결 
db.User = User;
db.Comment = Comment;

//init이 되어야 테이블이 모델로 연결 
User.initiate(sequelize);
Comment.initiate(sequelize);

//관계 연결 
User.associate(db);
Comment.associate(db);

//다른 곳에서도 같은 시퀄라이즈 객체를 사용할 수 있도록 exports
module.exports = db;
