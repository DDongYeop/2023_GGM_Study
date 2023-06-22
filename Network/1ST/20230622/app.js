const express = require('express');
const cookieParser = require('cookie-parser');
const session = require('express-session');
const morgan = require('morgan');
const path = require('path');
const nunjucks = require('nunjucks');
const dotenv = require('dotenv');
const {sequelize} = require('./models');
const passport = require('passport');
const passportConfig = require('./passport');

passportConfig();
dotenv.config();

// 로그인 화면, 프로필 화면, 메인 화면 등등을 page.js에서 라우팅
const pageRouter = require('./routes/page');
const authRouter = require('./routes/auth');

const app = express();
app.set('port', 8001);
app.set('view engine', 'html');
nunjucks.configure('views',{
    express: app,
    watch: true,
});
sequelize.sync().then(() =>
{
    console.log('DB 연결 성공');
})
.catch((err)=>
{
    console.error(err);
})

app.use(morgan('dev'));
// public 폴더에서 파일 제공, 정적 파일을 프론트에서 접근 가능
app.use(express.static(path.join(__dirname, 'public')));
// json, form 요청을 받을 수 있게 함
app.use(express.json());
app.use(express.urlencoded({extended:false}));
app.use(cookieParser(process.env.COOKIE_SECRET));
app.use(session({
    resave:false,
    saveUninitialized: false,
    secret: process.env.COOKIE_SECRET,
    cookie:{
        httpOnly:true,
        secure: false,
    }
}));
app.use(passport.initialize());
app.use(passport.session()); // -->패스포트 모듈이 req.user req.login 등등 로그인에 필요한거 생성 

// 여기까지 nodejs 기본 세팅

// localhost:8001
app.use('/', pageRouter);
app.use('/auth', authRouter);

// 404 NOT FOUNT
app.use((req, res, next)=>{
    const error = new Error(`${req.method} ${req.url} 라우터가 없습니다}`);
    error.status = 404;
    next(error);
});

// 나머지 에러 처리
app.use((err, req, res, next)=>{
    res.locals.message = err.message;
    res.locals.error = process.env.NODE_ENV !== 'producion' ? err:{};
    res.status(err.stats || 500);
    res.render('error'); 
    // render는 넌척스가 views 폴더에서 error.html 파일 찾아서 응답
});

app.listen(app.get('port'),()=>{
    console.log(app.get('port'), '번 포트에서 대기중 ');
});