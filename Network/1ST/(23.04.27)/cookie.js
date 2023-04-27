const http = require('http');

http.createServer((req, res) =>
{
    console.log(req.url, req.headers.cookie);
    res.writeHead(200, {'Set-Cookie': 'mycookie=test'});
    res.end('Hello Cookie');
})
.listen(8084, () =>
{
    console.log('8084번 포트에서 실행중');
});
