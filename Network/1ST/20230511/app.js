const express = require('express');
const path = require('path');

const app = express();
//서버에다가 변수 설정
app.set('port', 3000);

app.use((req, res, next) =>
{
    console.log('모든 요청에 다 실행됩니다.');
    next();
})

app.get('*');

app.get('/', (req, res, next) =>
{
    console.log('Get /요청에서만 실행됩니다.');
    //res.send('Hello 김민수');
    res.sendFile(path.join(__dirname, '/index.html'));
});

app.get('/category/park', (req, res) =>
{
    res.send(`부성아 왜 그랫어`);
})

app.get('/category/:name', (req, res) =>
{
    res.send(`hello ${req.params.name}`);
});

app.use((err, req, res, next) =>
{
    console.err(err);
    res.send('에러남');
})

app.listen(app.get('port'), () =>
{
    console.log(app.get('port'), '번 포트에서 실행중');
});
