const bcrypt = require('bcrypt');
const passport = require('passport');
const User = require('../models/user');

// 1.회원가임 -> db에 저장하면 됨
exports.join = async(req, res, next) =>
{
    const {email, nick, password} = req.body; //프론트에서 받은 정보
    try 
    {
        //기존 사용자가 있는지 확인
        const exUser = await User.findOne({where: {email}});
        if (exUser)
        {
            return res.redirect('/join?error=exist'); //해당 유저 존재 
        }
        const hash = await bcrypt.hash(password, 12);
        await User.create({
            email,
            nick,
            password:hash
        });
        return res.redirect('/');
    }
    catch (err)
    {
        console.error(err);
        return next(err);
    }
}

// 2. 로그인
exports.login = (req, res, next) =>
{
    passport.authenticate('local', (authError, user, info) =>{
        if (authError)
        {
            console.error(authError);
            return next(authError);
        }
        if (!user)
        {
            return res.redirect(`/?loginError=${info.message}`)
        }
        return req.login(user, (logError) =>
        {
            if (loginError)
            {

            }
            return res.redirect('/'); //로그인 완료 
        })
    })(req, res, next);
}

//3.로그아웃
exports.logout = (req, res) =>
{
    req.logout(() =>{
        res.redirect('/');
    });
}