exports.renderProfile = (req, res) =>{
    // 라우터 -> 컨트롤러 -> 서비스
    res.render('profile', {title: '내 정보 - NodeSNS'});
    // 넌적스가 views 폴더에서 profile.html을 찾아서 응답
    // 매개변수로 프로트에 넘기고 싶은 정보 전달
}

exports.renderJoin = (req, res) =>{
    res.render('join', {title: '회원가입 - NodeSNS'});
}

exports.renderMain = (req, res) =>{
    const twits = [];
    res.render('main', {
        title: 'NodeSNS',
        twits,
    });
}
