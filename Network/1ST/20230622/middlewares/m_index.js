//두 개의 미들웨어를 만들거다.
//로그인 했는지 판단하는 미들웨어, 로그인 안 했는지 판단하는 미들웨어

exports.isLoggedIn = (req, res, next) => {
    if (req.isAuthenticated()) { //패스포트 통해서 로그인 했니
      next();
    } else {
      res.status(403).send('로그인 필요');
    }
};
  
exports.isNotLoggedIn = (req, res, next) => {
    if (!req.isAuthenticated()) {
      next();
    } else { //로그인 이미 했다면 
      const message = encodeURIComponent('로그인한 상태입니다.');
      res.redirect(`/?error=${message}`);
    }

    //이걸 만든 이유는,  routes/page.js 수정
};