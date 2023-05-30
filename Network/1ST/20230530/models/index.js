const Sequelize = require('sequelize');

const env = process.env.NODE_ENV || 'development';
const config = require(__dirname + '/../config/config.json')[env];
const db = {};

//config.json에 있는 DB값으로 새로운 시퀄라이즈ㅡ 객체 생성 
const sequelize = new Sequelize(config.database, config.username, config.password, config);

db.sequelize = sequelize;

//다른 곳에서도 같은 시퀄라이즈 객체를 사용할 수 있도록 exports
module.exports = db;
