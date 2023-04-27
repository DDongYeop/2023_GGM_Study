const http = require('http');
const fs = require('fs').promises;
const path = require('path');

const users = {};

http.createServer(async (req, res) =>
{
    try
    { 
        if (req.method === 'GET')
        {
            if (req.url === '/') // 1.localhost:8083/ 주소를 입력했을 때 응답하는 부분
            {
                const data = await fs.readFile(path.join(__dirname, 'restFront.html'));
                // fs.readFile('./restFront.html);
                res.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'});
                return res.end(data);
            }
            if (req.url === '/about')
            {
                const data = await fs.readFile(path.join(__dirname, 'about.html'));
                // fs.readFile('./restFront.html);
                res.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'});
                return res.end(data);
            }
            else if (req.url === '/users') //유저 정보를 JSON으로 보내준다
            {
                res.writeHead(200, {'Content-Type': 'application/json; charset=utf-8'});
                return res.end(JSON.stringify(users));
            }
            try
            {
                const data = await fs.readFile(path.join(__dirname, req.url));
                return res.end(data);
            }
            catch(err)
            {

            }
        }
        else if (req.method === 'POST')
        {
            if (req.url == '/user')
            {
                // 스츠림 방식으로 데이터 받아오기
                let body = '';
                req.on('data', (data) =>
                {
                    body += data;
                });
                //data가 더 이상 없을때
                return req.on('end', () =>
                {
                    console.log('post 본문: ', body);
                    // {name}을 전달받으면
                    const { name } = JSON.parse(body);
                    const id = Date.now();
                    users[id] = name;
                    res.writeHead(201, {'Content-Type': 'text/plain; charset=utf-8'});
                    res.end(JSON.stringify(users));
                })
            }
        }
        res.writeHead(404);
        return res.end('NOT FOUNT');
    }
    catch(err)
    {
        console.error(err);
        res.writeHead(500, {'Content-Type': 'text/plain; charset=utf-8'});
        res.end(err.message);
    }
})
.listen(8083, () =>
{
    console.log('8083번 포트에서 대기중 . . .');
})
