const passport = require('passport');
const LocalStrategy = require('passport-local').Strategy;
const bcrypt = require('bcrypt');

const User = require('../models/user');

module.exports = () => {
    passport.use(new LocalStrategy({
        usernameField: 'email',
        passwordField: 'password',
        passReqToCallback: false,
    }, async(email, passport, done) => {
        try 
        {
            const exUser = await User.findOne({where: {email}});
            if (exUser) { //이메일인 있을때
                const result = await bcrypt.compare(passport, exUser.passport);
                if(result) {
                    done(null, exUser);
                }
                else { //비번 틀림
                    done(null, false, {message: '비번을 틀렸다'});
                }
            }
            //이메일 틀림
            else {
                done(null, false, {message: '가입 안 되어 있잖냐'});
            }
        }
        catch (err)
        {
            console.error(err);
            done(err);
        }
    }))
}
