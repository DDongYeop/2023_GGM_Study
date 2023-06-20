const express = require('express');
const cookieParser = require('cookie-parser');
const session = require('express-session');
const morgan = require('morgan');
const path = require('path');
const nunjucks = require('nunjucks');
const dotenv = require('dotenv');

dotenv.config();

//로그인 화면, 프로필 화면, 메인 화면 등등을 page.js에서 라우팅
const pageRouter = require('./routes/page');
const { watch } = require('fs');

const app = express;
app.set('port', 8001);
app.set('view engine', 'html');
nunjucks.configure('views', 
{
    express: app,
    watch: true,
});

app.use(morgan('dev'));
//public 폴더에서 정적 파일 제공. 정적파일을 프로트에서 접근 가능
app.use(express.static(path.join(__dirname, 'public')));
//json, form 요청을 받을 수 있게 함
app.use(express.json());
app.use(express.urlencoded({extended:false}));
app.use(cookieParser(process.env.COOKIE_SECRET));
app.use(session (
{
    resave:false,
    saveUninitialized: false,
    secret: process.env.COOKIE_SECRET,
    cookie:
    {
        httpOnly:true,
        secure: false,
    }
}));

//여기까지는 nodejs 프로젝트 기본 세팅

//localhost:8001
app.use('/', pageRouter);

//404 NOT FOUND
app.use((req, res, next) =>
{
    const error = new Error (`${req.method} ${req.url} 라우터가 없습니다.`);
    error.status = 404;
    next(error);
});

//나머지 에러 처리
app.use((err, req, res, next) =>
{
    res.locals.message = err.message;
    res.locals.error = process.env.NODE_ENV !== 'production' ? err : {};
    res.status(err.status || 500);
    res.render('error'); //render는 넌적스가 views 폴더에서
    //error.html이라는 파일을 찾아가지고 응답 
});

app.listen(app.get('port'), () =>
{
    console.log(app.get('port'), '번 포트에서 대기중');
});
