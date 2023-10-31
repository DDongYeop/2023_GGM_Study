#include "pch.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Texture.h"
#include "PathMgr.h"

Player::Player() : m_pTex(nullptr)
{
	m_pTex - new Texture;
	wstring strFilePath = PathMgr::GetInst()->GetResPath();
	strFilePath += L"Texture\\planem.bmp";
	m_pTex->Load(strFilePath);
}

Player::~Player()
{
	if (nullptr != m_pTex)
		delete m_pTex;
}

void Player::Update()
{
	Vec2 vPos = GetPos();
	if (KEY_PRESS(KEY_TYPE::LEFT))
	{
		//m_obj.m_ptPos.x -= 1;
		vPos.x -= 100.f * fDT;
	}
	if (KEY_PRESS(KEY_TYPE::RIGHT))
	{
		//m_obj.m_ptPos.x += 1;
		vPos.x += 100.f * fDT;
	}
	if (KEY_DOWN(KEY_TYPE::SPACE))
		CreateBullet();
	SetPos(vPos);
}

void Player::CreateBullet()
{
	Bullet* pBullet = new Bullet;
	Vec2 vBulletPos = GetPos();
	vBulletPos.y -= GetScale().y / 2.f;
	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vec2(25, 25));
	//pBullet->SetDir(120 * M_PI / 180);
	pBullet->SetDir(Vec2(-10, -15));
	SceneMgr::GetInst()->GetCurScnee()->AddObject(pBullet, OBJECT_GROUP::BULLET);
}

void Player::Render(HDC _dc)
{
	//비트맵 띄우기
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();
	//색상 걷어내기
	//GdiTransparentBlt(_dc, (int)(vPos.x - vScale.x / 2), (int)(vPos.y, vScale.y / 2), Width, Height, m_pTex->GetDC(), 0, 0, Width, Height, RGB(255, 0, 255));
	
	//확대 및 축소
	GdiTransparentBlt(_dc, (int)(vPos.x - vScale.x / 2), (int)(vPos.y, vScale.y / 2), Width * 2, Height * 2, m_pTex->GetDC(), 0, 0, Width, Height, SRCCOPY);
}

