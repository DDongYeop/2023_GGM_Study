const Sequelize = require('sequelize');

class Post extends Sequelize.Model {
  static initiate(sequelize) {
    Post.init({
      content: { //댓글 내용
        type: Sequelize.STRING(140),
        allowNull: false,
      },
      img: { //댓글에 이미지 올릴 수 있(하나씩)
        type: Sequelize.STRING(200),
        allowNull: true,
      },
    }, {
      sequelize,
      timestamps: true,
      underscored: false,
      modelName: 'Post',
      tableName: 'posts',
      paranoid: false,
      charset: 'utf8mb4', //mb4는 이모티콘도 가능
      collate: 'utf8mb4_general_ci',
    });
  }
  
  static associate(db) {
    db.Post.belongsTo(db.User);
    db.Post.belongsToMany(db.Hashtag, {through: 'PostHashtag'});
  }
}

module.exports = Post;