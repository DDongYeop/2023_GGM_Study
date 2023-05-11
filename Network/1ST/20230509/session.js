const http = require('http');
const fs = require('fs').promises;
const path = require('path');

const session = {}; //서버 쪽 데이터 저장용 객체

const parseCookies = (cookie = '') =>
    cookie
    .split(';') //배열
    .map(v => v.split('='))
    .reduce((acc, [k, v]) => {
        acc[k.trim()] = decodeURIComponent(v); //trim 앞뒤 공백 및 문자 제거
        return acc;
    }, {}); //객체 반환, {name: '123'}

http.createServer(async (req, res) => {
    const cookies = parseCookies(req.headers.cookie);

    // 3.
    // 주소가 /login으로 시작하는 경우 Get 요청처리
    if (req.url.startsWith('/login')) 
    {
        const url = new URL(req.url, 'http://localhost:8084');
        const name = url.searchParams.get('name');
        const expires = new Date();
        // 쿠키 유효 시간을 현재 시간 +5 설정
        expires.setMinutes(expires.getMinutes() + 5);

        //세션에 키 제공. 여기서는 현재 시간으로 키 설정
        //uniqueID
        const uniqueInt = Date.now();
        session[uniqueInt] = 
        {
            name,
            expires,
        }

        // 302 redireection 이 주소로 다시 돌려보낸다
        res.writeHead(302, { Location: '/', 'Set-Cookie': `session=${uniqueInt}; Expires=${expires.toGMTString()}; HttpOnly; Path=/` });
        res.end();
    }
    // 2.
    // 로그인 하면 뜨는 창
    // 주소가 '/'이면서 name이라는 쿠키가 있는 경우
    // 쿠키가 있는 경우
    else if (cookies.session && session[cookies.session].expires > new Date())
    { 
        res.writeHead(200, { 'Content-Type': 'text/plain; charset=utf-8' });
        res.end(`${session[cookies.session].name}님 안녕하세요?`);
    }
    // 1. 
    // 여기가 제일 먼저 실행 
    // 쿠키가 없는 여우에는 로그인할 수 있는 페이지 응답
    // 주소가 '/' 이면서 name이라는 쿠키가 없을떄
    else 
    {
        try 
        {
            const data = await fs.readFile(path.join(__dirname, 'cookie.html'));
            res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
            res.end(data);
        }
        catch (err) 
        {
            res.writeHead(500, { 'Content-Type': 'text/plain; charset=utf-8' });
            res.end(err.message);
        }
    }
})
.listen(8084, () => 
{
    console.log('8084번 포트에서 서버 대기 중');
})
