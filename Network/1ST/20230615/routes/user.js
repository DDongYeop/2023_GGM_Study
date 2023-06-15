const express = require('express');
const User = require('../models/user');
const Comment = require('../models/comment');

const router = express.Router();

//localhost:3000/users
router.route('/')
.get(async(req, res, next) =>
{
    try
    {
        //사용자 조회
        const users = await User.findAll();
        res.json(users);
    }
    catch(err)
    {
        console.error(err);
        next(err);
    }
})
.post(async(req, res, next) =>
{
    try
    {
        //사용자 등록
        const user = await User.create({
            //화면에서 입력한 내용을 받아서 저장
            name: req.body.name,
            age: req.body.age,
            married: req.body.married
        });
        console.log(user);
        res.status(201).json(user);
    }
    catch(err)
    {
        console.error(err);
        next(err);
    }
})

//localhost:3000/users/:id/comments
router.get('/:id/comments', async(req, res, next) =>
{
    try
    {
        const comments = await Comment.findAll({
            include:
            {
                model: User,
                where: {id: req.params.id},
            }
        });
        console.log(comments);
        res.json(comments);
    }
    catch(err)
    {
        console.error(err);
        next(err);
    }
})
module.exports = router;
