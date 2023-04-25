const { error } = require('console');
const http = require('http');

const server = http.createServer((req, res) =>
{
    res.writeHead(200, {'Content-Type' : 'text/html; charset=utf-8'});
    res.write('<h1>Hello GGM</h1>');
    res.end('<p>Hello Server!</p>');
}); 
server.listen(8080, () =>
{
    console.log('8080번 포트에서 서버 대기 중');
});
//server.listen(8080);

server.on('listening', () =>
{
    console.log('8080번 포트에서 서버 대기 중!');
});
server.on('error', (error) =>
{
    console.error(error);
});



// 실행시켜둔 상태에서
// localhost:포트번호
