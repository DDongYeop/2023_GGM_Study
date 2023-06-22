const express = require('express');
const passport = require('passport');

const { isLoggedIn, isNotLoggedIn } = require('../middlewares/m_index');
const { join, login, logout } = require('../controllers/auth');

const router = express.Router();

// POST /auth/join 로그인 안 한 사람들이 회원가입 --> 그래서 아까 그 미들웨어부터 만들어 놓은 거
router.post('/join', isNotLoggedIn, join); 

//POST /auth/login 로그인 안 한 사람들이 로그인
router.post('/login', isNotLoggedIn, login);

//GET /auth/logout 로그인 한 사람들이 로그아웃
router.get('/logout', isLoggedIn, logout);

/*
//GET /auth/kakao
router.get('/kakao', passport.authenticate('kakao'));

// GET /auth/kakao/callback
router.get('/kakao/callback', passport.authenticate('kakao', {
  failureRedirect: '/?loginError=카카오로그인 실패',
}), (req, res) => {
  res.redirect('/'); // 성공 시에는 /로 이동
});

*/

module.exports = router;