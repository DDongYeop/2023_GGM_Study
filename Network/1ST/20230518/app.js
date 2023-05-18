const express = require('express');
const path = require('path');
const morgan = require('morgan');
const cookieParser = require('cookie-parser');
const dotenv = require('dotenv');

const app = express();
//서버에다가 변수 설정
app.set('port', 3000);
app.use(morgan('dev'));
app.use(cookieParser(procces.env.COOKIE_SECRET));

dotenv.config();

app.use((req, res, next) =>
{
    console.log('모든 요청에 다 실행됩니다.');
    next();
});


app.get('/category/park', (req, res) =>
{
    res.send(`부성아 왜 그랫어`);
})

app.get('/category/:name', (req, res) =>
{
    res.send(`hello ${req.params.name}`);
});


app.get('/', (req, res, next) =>
{
    if (req.cookies?.name)
    {
        res.send(`Hello ${req.cookies.name}`);
    }
    else
    {
        res.send('not cookie');
    }
});

app.get('/cookie', (req, res) =>
{
    res.cookie('name', 'Park', 
    {
        httpOnly: true,
        path: '/',
    }).redirect('/');
})

app.get('/delete', (req, res) =>
{
    res.clearCookie('name', 'Kim', {httpOnly: true, path: '/'});
    res.redirect('/');
})

//404 NOT FOUND 미들웨어
//모들 라우터 뒤 에러 처리 미드웨어 전
app.use((req, res, next) =>
{
    res.status(404).send('404 NOT FOUND');
})

//에러 처리 미들웨어
//매개 변수가 4개여야한다
app.use((err, req, res, next) =>
{
    console.error(err);
    res.send('에러남');
})

app.listen(app.get('port'), () =>
{
    console.log(app.get('port'), '번 포트에서 실행중');
});
