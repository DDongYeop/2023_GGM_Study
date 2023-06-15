const express = require('express');
//DB의 user모델
const User = require('../models/user');

const router = express.Router();

router.get('/', async(reeq, res, next) =>
{
    try
    {
        //등록되어 있는 모든 사용자를 찾아서 sequelize.html를 렌더링할 때 users를 넣음
        const users = await User.findAll(); //SELECT
        res.render('sequelize', {users});
        //단순한 문자열은 res.send
        //파일은 res.sendFile
        //템플릿 엔진 res.render
        //그외 json res.json
    }
    catch(err)
    {
        console.error(err);
        next(err);
    }
})

module.exports = router;
