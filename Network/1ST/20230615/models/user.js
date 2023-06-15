const Sequelize = require('sequelize');

class User extends Sequelize.Model {
    //테이블에 대한 설정
  static initiate(sequelize) {
    User.init({
      //id는 자동으로 생성해주기 때문에 생략
      name: {
        type: Sequelize.STRING(20),
        allowNull: false, //NOT NULL
        unique: true,
      },
      age: {
        type: Sequelize.INTEGER.UNSIGNED,
        allowNull: false,
      },
      married: {
        type: Sequelize.BOOLEAN,
        allowNull: false,
      },
      comment: {
        type: Sequelize.TEXT,
        allowNull: true,
      },
      created_at: {
        type: Sequelize.DATE,
        allowNull: false,
        defaultValue: Sequelize.NOW,
      },
    }, {
      //모델에 대한 설정
      sequelize,
      timestamps: false,
      underscored: false,
      modelName: 'User',
      tableName: 'users', //모델 이름을 소문자화 한 후 s를 붙이는게 테이블 이름 규칙
      paranoid: false,
      charset: 'utf8', //한글 설정 위해
      collate: 'utf8_general_ci',
    });
  }
  static associate(db)
  {
    db.User.hasMany(db.Comment, {foreignKey: 'commenter', sourceKey: 'id'});
  }
};

module.exports = User;