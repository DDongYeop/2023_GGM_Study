//passport 설정을 여기서 함

const passport = require('passport');
const local = require('./localStrategy'); //이메일 로그인
//const kakao = require('./kakaoStrategy'); //카카오 로그인
const User = require('../models/user'); //유저 모델 가져오기(회원가입을 위해 유저 테이블에 데이터 저장)

//이 함수가 app.js에서 불러와져서 실행. passportConfig(); 호출한 곳에서

module.exports = () => {
    //passport는 크게 serialize, deserialize로 나뉨
  passport.serializeUser((user, done) => { 
    done(null, user.id);
  });

  passport.deserializeUser((id, done) => { //세션쿠키로부터 온 아이디를 가지고
    User.findOne({ where: { id } }) //유저를 찾아서
      .then(user => done(null, user)) //req.user 객체를 사용할 수 있게 됨
      .catch(err => done(err));
  });

  //passport.authenticate 메소드가 호출되면
  //local이냐 kakao냐에 따라서 각각 localStrategy, kakaoStrategy 호출
  local();
  //kakao();
};