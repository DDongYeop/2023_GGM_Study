const express = require('express');
const {renderProfile, renderJoin, renderMain} = require('../controllers/page');
const {isLoggedIn, isNotLoggedIn} = require('../middlewares/m_index');

const router = express.Router();

// 라우터에서 공통적으로 사용할 변수들을 설정
router.use((req, res, next) =>{
    res.locals.user = req.user;//사용자 정의
    res.locals.followerCount = 0;
    res.locals.followinCount = 0;
    res.locals.followingIdList = [];
    next();
});

// 한 번 더 각각의 페이지를 분리
router.get('/profile', isLoggedIn, renderProfile);
router.get('/join', isNotLoggedIn, renderJoin);
router.get('/', renderMain);

module.exports = router;