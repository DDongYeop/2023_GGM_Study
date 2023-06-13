const express = require('express');
const path = require('path');
const morgan = require('morgan');
const cookieParser = require('cookie-parser');
const dotenv = require('dotenv');
const bodyParser = require('body-parser');
const session = require('express-session');
const multer = require('multer');
const fs = require('fs');
const categoryRouter = require('./routes/category');
const nunjucks = require('nunjucks');

//index.js에서 exports한 시쿠럴라이즈 객체 가져오기
//서버 실행 시 mySQL연동을 위한 db.dequelize
const {sequelize} = require('./models/index');

dotenv.config();

const app = express();
//서버에다가 변수 설정
app.set('port', 3000);
app.set('view engine', 'html'); //확장자명 html 쓸거다 
nunjucks.configure('views', {
    express: app,
    watch:true,
});

//mySQL이랑 연동하는 부분
sequelize.sync({force:false})
.then(() =>
{
    console.log('데이터베이스 연결 성공');
})
.catch((err)=>
{
    console.log(err);
});

app.use(morgan('dev'));
dotenv.config();
app.use(cookieParser(process.env.COOKIE_SECRET));
app.use(express.urlencoded({extended:false}));
app.use(session(
    {
    resave:false,
    saveUninitialized:false,
    secret:process.env.COOKIE_SECRET,
    cookie:
    {
        httpOnly:true,
        secure:false,
    },
    name:'session-cookie',
}));

try
{
    fs.readdirSync('uploads');
}
catch (err)
{
    console.error('uploads folder is not');
    fs.mkdirSync('uploads');
}

const upload = multer(
{
    storage: multer.diskStorage(
    {
        destination(req, file, done)
        {
            done(null, 'uploads/');
        },
        filename(req, file, done)
        {
            const ext = path.extname(file.originalname);
            done(null, path.basename(file.originalname, ext) + Date.now() + ext);
        },
    }),
    limits: {fileSize: 5*1024*1024},
});

app.get('/upload', (req, res) =>
{
    res.sendFile(path.join(__dirname, '/multipart.html'));
});

app.post('/upload', upload.array('image'), (req, res) =>
{
    console.log(req.files);
    res.send('ok');
})

app.use((req, res, next) =>
{
    console.log('모든 요청에 다 실행됩니다.');
    next();
});

app.use('/category', categoryRouter);

app.get('/', (req, res, next) =>
{
    if (req.session?.name)
    {
        res.send(`Hello ${req.session.name}`);
    }
    else
    {
        res.sendFile(path.join(__dirname, '/session_index.html'));
    }
});

app.post('/', (req, res) =>
{
    req.session.name = req.body.name;
    res.redirect('/');
})

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
    req.session.destroy();
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
