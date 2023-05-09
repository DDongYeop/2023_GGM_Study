const cluster = require('cluster');
const http = require('http');
const numCPUs = require('os').cpus().length; //코어 개수

if (cluster.isMaster)
{
    console.log(`마스터 프로세스 아이디: ${process.pid}`);
    
    //CPU개수만큼 워커 생성
    for (let i = 0; i < numCPUs; i++)
    {
        cluster.fork();
    }

    //워커 종료시
    cluster.on('exit', (worker, code, signal) =>
    {
        console.log(`${worker.process.pid}번 워커가 종료되었습니다.`);
        console.log('code', code, 'signal', signal);
    });
}
else //워커들
{
    http.createServer((req, res) =>
    {
        res.writeHead(200, {'Context-Type': 'text/html; charset=utf-8'});
        res.end('<h1>I want go home</h1>');
    }).listen(8085);

    console.log(`${process.pid}번 워커 실행`);
}