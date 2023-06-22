const Sequelize = require('sequelize');

class User extends Sequelize.Model {
  static initiate(sequelize) { //테이블정보
    User.init({
      email: { //이메일
        type: Sequelize.STRING(40),
        allowNull: true, //카카오톡 로그인 할 때는 이메일 비워줘도 됨
        unique: true,
      },
      nick: { //닉네임
        type: Sequelize.STRING(15),
        allowNull: false,
      },
      password: { //비번(암호화 되면 길어짐)
        type: Sequelize.STRING(100),
        allowNull: true,
      },
      provider: {
        type: Sequelize.ENUM('local', 'kakao'), //로컬 카카오 둘 중 하나만 제한
        allowNull: false,
        defaultValue: 'local',
      },
      snsId: { //SNS를 통해 로그인 할 때의 ID(이메일 같은 역할)
        type: Sequelize.STRING(30),
        allowNull: true,
      },
    }, {
      sequelize,
      timestamps: true,
      underscored: false,
      modelName: 'User', //자바스크립트에서 쓰는 이름
      tableName: 'users', //DB에서 사용하는 테ㅣ블 이름
      paranoid: true,
      charset: 'utf8',
      collate: 'utf8_general_ci',
    });
  }

  static associate(db) { //테이블 관계
    db.User.hasMany(db.Post);
    db.User.belongsToMany(db.User, {
      foreignKey: 'followingId',
      as: 'Followers',
      through: 'Follow',
    });
    db.User.belongsToMany(db.User, {
      foreignKey: 'followerId',
      as: 'Followings',
      through: 'Follow',
    });
  }
};

module.exports = User;