const express = require('express');

const app = express();
//서버에다가 변수 설정
app.set('port', 3000);

app.get('/', (req, res) =>
{
    res.send('Hello 김민수');
});

app.listen(app.get('port'), () =>
{
    console.log(app.get('port'), '번 포트에서 실행중');
});
