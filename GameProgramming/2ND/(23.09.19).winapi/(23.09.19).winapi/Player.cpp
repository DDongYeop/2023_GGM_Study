#include "pch.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"

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
	SceneMgr::GetInst()->GetCurScnee()->AddObject(pBullet, OBJECT_GROUP::BULLET);
}

