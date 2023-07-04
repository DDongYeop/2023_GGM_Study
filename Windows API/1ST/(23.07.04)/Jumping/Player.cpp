#include "pch.h"
#include "Player.h"

Player::Player()
	: Pawn(0, 0)
{
	m_state = PLAYER_STATE::RIGHT_IDLE;
	m_beforeState = m_state;

	m_isGround = false;
	m_canMoveRight = false;
	m_canMoveLeft = false;

	m_isMoving = false;

	m_gravity = GRAVITY;
	m_velocity = VELOCITY;
}

Player::Player(float x, float y, int width, int height, float scale, float speed)
	: Pawn(x, y, width, height, scale, speed)
{
	m_state = PLAYER_STATE::RIGHT_IDLE;
	m_beforeState = m_state;

	m_isGround = false;
	m_canMoveRight = false;
	m_canMoveLeft = false;

	m_isMoving = false;

	m_gravity = GRAVITY;
	m_velocity = VELOCITY;

	m_fMaxHP = 5;
	m_fHP = m_fMaxHP;
}

Player::~Player()
{
}

void Player::Init()
{
	m_imgPlayerList.resize((UINT)PLAYER_IMAGE::COUNT);
	
	m_imgPlayerList[(UINT)PLAYER_IMAGE::IDLE] = GET_SINGLE(ImageManager)->AddImage(L"IDLE", L"Resources/Player/Idle_24.bmp");
	m_imgPlayerList[(UINT)PLAYER_IMAGE::MOVE] = GET_SINGLE(ImageManager)->AddImage(L"MOVE", L"Resources/Player/Walk_26.bmp");
	m_imgPlayerList[(UINT)PLAYER_IMAGE::JUMP] = GET_SINGLE(ImageManager)->AddImage(L"JUMP", L"Resources/Player/Jump_28.bmp");
	m_imgPlayerList[(UINT)PLAYER_IMAGE::DEAD] = GET_SINGLE(ImageManager)->AddImage(L"DEAD", L"Resources/Player/Death_28.bmp");

	m_aniPlayerList.resize((UINT)PLAYER_IMAGE::COUNT);

	int width = 0, height = 0;
	shared_ptr<Animation> idleAni = make_shared<Animation>();
	width = m_imgPlayerList[(UINT)PLAYER_IMAGE::IDLE]->GetWidth();
	height = m_imgPlayerList[(UINT)PLAYER_IMAGE::IDLE]->GetHeight();
	idleAni->Init(width, height, width / 4, height / 2);
	m_aniPlayerList[(UINT)PLAYER_IMAGE::IDLE] = std::move(idleAni);

	shared_ptr<Animation> moveAni = make_shared<Animation>();
	width = m_imgPlayerList[(UINT)PLAYER_IMAGE::MOVE]->GetWidth();
	height = m_imgPlayerList[(UINT)PLAYER_IMAGE::MOVE]->GetHeight();
	moveAni->Init(width, height, width / 6, height / 2);
	m_aniPlayerList[(UINT)PLAYER_IMAGE::MOVE] = std::move(moveAni);

	shared_ptr<Animation> jumpAni = make_shared<Animation>();
	width = m_imgPlayerList[(UINT)PLAYER_IMAGE::JUMP]->GetWidth();
	height = m_imgPlayerList[(UINT)PLAYER_IMAGE::JUMP]->GetHeight();
	jumpAni->Init(width, height, width / 8, height / 2);
	m_aniPlayerList[(UINT)PLAYER_IMAGE::JUMP] = std::move(jumpAni);

	shared_ptr<Animation> deadAni = make_shared<Animation>();
	width = m_imgPlayerList[(UINT)PLAYER_IMAGE::DEAD]->GetWidth();
	height = m_imgPlayerList[(UINT)PLAYER_IMAGE::DEAD]->GetHeight();
	deadAni->Init(width, height, width / 8, height / 2);
	m_aniPlayerList[(UINT)PLAYER_IMAGE::DEAD] = std::move(deadAni);

	m_state = PLAYER_STATE::RIGHT_IDLE;
	m_beforeState = m_state;
	SetAnimation(m_state);
}

void Player::Update(float dt)
{
	m_isMoving = false;
	if (INPUT->GetButtonDown(KEY_TYPE::RIGHT))
	{
		m_beforeState = PLAYER_STATE::RIGHT_MOVE;
		if (!IsJumping() && !IsFalling())
			SetAnimation(PLAYER_STATE::RIGHT_MOVE);
	}
	if (INPUT->GetButton(KEY_TYPE::RIGHT))
	{
		m_beforeState = PLAYER_STATE::RIGHT_MOVE;
		if ( IsRight() && m_canMoveRight )
		{
			m_fPosX += m_fSpeed * dt;
			m_isMoving = true;
		}
	}
	if (INPUT->GetButtonUp(KEY_TYPE::RIGHT))
	{
		m_beforeState = PLAYER_STATE::RIGHT_IDLE;
		if (m_isGround)
			SetAnimation(PLAYER_STATE::RIGHT_IDLE);
	}

	if (INPUT->GetButtonDown(KEY_TYPE::LEFT))
	{
		m_beforeState = PLAYER_STATE::LEFT_MOVE;
		if (!IsJumping() && !IsFalling())
			SetAnimation(PLAYER_STATE::LEFT_MOVE);
	}
	if (INPUT->GetButton(KEY_TYPE::LEFT))
	{
		m_beforeState = PLAYER_STATE::LEFT_MOVE;
		if (IsLeft() && m_canMoveLeft)
		{
			m_fPosX -= m_fSpeed * dt;
			m_isMoving = true;
		}
	}
	if (INPUT->GetButtonUp(KEY_TYPE::LEFT))
	{
		m_beforeState = PLAYER_STATE::LEFT_IDLE;
		if (m_isGround)
			SetAnimation(PLAYER_STATE::LEFT_IDLE);
	}

	if (INPUT->GetButtonDown(KEY_TYPE::SPACE))
	{
		if (!IsJumping() && !IsFalling() && m_isGround)
		{
			m_isGround = false;
			m_velocity = VELOCITY;
			if (IsRight())
				SetAnimation(PLAYER_STATE::RIGHT_JUMP);
			else
				SetAnimation(PLAYER_STATE::LEFT_JUMP);
		}
	}

	if ((IsJumping() || IsFalling()) && m_isGround == false)
	{
		m_fPosY -= m_velocity * dt;
		m_velocity += m_gravity * dt;
	}

	if (!m_isGround)
	{
		m_fPosY += m_fSpeed * dt;
	}

	if (m_aniPlayer)
		m_aniPlayer->Update(dt);

	switch (m_state)
	{
	case PLAYER_STATE::RIGHT_JUMP:
		if (m_velocity <= 0)
			SetAnimation(PLAYER_STATE::RIGHT_FALL);
		break;
	case PLAYER_STATE::LEFT_JUMP:
		if (m_velocity <= 0)
			SetAnimation(PLAYER_STATE::LEFT_FALL);
		break;
	case PLAYER_STATE::RIGHT_FALL:
	case PLAYER_STATE::LEFT_FALL:
		if (m_isGround)
		{
			m_state = m_beforeState;
			SetAnimation(m_state);
		}
		break;
	default:
		break;
	}
}

void Player::Render(HDC hdc)
{
	if(m_imgPlayer)
		m_imgPlayer->DrawAnimation(hdc, m_fPosX, m_fPosY, m_aniPlayer);

	// µð¹ö±ë¿ë RECT
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, m_fPosX - m_nWidth / 2, m_fPosY - m_nHeight / 2,
				   m_fPosX + m_nWidth / 2, m_fPosY + m_nHeight / 2);
}

void Player::Release()
{
	m_imgPlayer = nullptr;
	for (UINT i = 0; i < (UINT)m_imgPlayerList.size(); ++i)
	{
		m_imgPlayerList[i]->Release();
		m_imgPlayerList[i] = nullptr;
	}
	m_imgPlayerList.clear();

	m_aniPlayer = nullptr;
	for (UINT i = 0; i < (UINT)m_aniPlayerList.size(); ++i)
	{
		m_aniPlayerList[i]->Release();
		m_aniPlayerList[i] = nullptr;
	}
	m_aniPlayerList.clear();


}

void Player::SetAnimation(PLAYER_STATE state)
{
	for (UINT i = 0; i < (UINT)m_aniPlayerList.size(); ++i)
		m_aniPlayerList[i]->Stop();

	m_state = state;

	switch (state)
	{
	case PLAYER_STATE::RIGHT_IDLE:
		m_imgPlayer = m_imgPlayerList[(UINT)PLAYER_IMAGE::IDLE];
		m_aniPlayer = m_aniPlayerList[(UINT)PLAYER_IMAGE::IDLE];
		m_aniPlayer->SetPlayFrame(0, 3, FALSE, TRUE);
		m_aniPlayer->Start();

		m_nWidth = m_aniPlayer->GetFrameWidth();
		m_nHeight = m_aniPlayer->GetFrameHeight();
		break;
	case PLAYER_STATE::LEFT_IDLE:
		m_imgPlayer = m_imgPlayerList[(UINT)PLAYER_IMAGE::IDLE];
		m_aniPlayer = m_aniPlayerList[(UINT)PLAYER_IMAGE::IDLE];
		m_aniPlayer->SetPlayFrame(4, 7, TRUE, TRUE);
		m_aniPlayer->Start();

		m_nWidth = m_aniPlayer->GetFrameWidth();
		m_nHeight = m_aniPlayer->GetFrameHeight();
		break;
	case PLAYER_STATE::RIGHT_MOVE:
		m_imgPlayer = m_imgPlayerList[(UINT)PLAYER_IMAGE::MOVE];
		m_aniPlayer = m_aniPlayerList[(UINT)PLAYER_IMAGE::MOVE];
		m_aniPlayer->SetPlayFrame(0, 5, FALSE, TRUE);
		m_aniPlayer->Start();

		m_nWidth = m_aniPlayer->GetFrameWidth();
		m_nHeight = m_aniPlayer->GetFrameHeight();
		break;
	case PLAYER_STATE::LEFT_MOVE:
		m_imgPlayer = m_imgPlayerList[(UINT)PLAYER_IMAGE::MOVE];
		m_aniPlayer = m_aniPlayerList[(UINT)PLAYER_IMAGE::MOVE];
		m_aniPlayer->SetPlayFrame(6, 11, TRUE, TRUE);
		m_aniPlayer->Start();

		m_nWidth = m_aniPlayer->GetFrameWidth();
		m_nHeight = m_aniPlayer->GetFrameHeight();
		break;
	case PLAYER_STATE::RIGHT_JUMP:
		m_imgPlayer = m_imgPlayerList[(UINT)PLAYER_IMAGE::JUMP];
		m_aniPlayer = m_aniPlayerList[(UINT)PLAYER_IMAGE::JUMP];
		m_aniPlayer->SetPlayFrame(3, 3, FALSE, FALSE);
		m_aniPlayer->Start();

		m_nWidth = m_aniPlayer->GetFrameWidth();
		m_nHeight = m_aniPlayer->GetFrameHeight();
		break;
	case PLAYER_STATE::LEFT_JUMP:
		m_imgPlayer = m_imgPlayerList[(UINT)PLAYER_IMAGE::JUMP];
		m_aniPlayer = m_aniPlayerList[(UINT)PLAYER_IMAGE::JUMP];
		m_aniPlayer->SetPlayFrame(12, 12, TRUE, FALSE);
		m_aniPlayer->Start();

		m_nWidth = m_aniPlayer->GetFrameWidth();
		m_nHeight = m_aniPlayer->GetFrameHeight();
		break;
	case PLAYER_STATE::RIGHT_FALL:
		m_imgPlayer = m_imgPlayerList[(UINT)PLAYER_IMAGE::JUMP];
		m_aniPlayer = m_aniPlayerList[(UINT)PLAYER_IMAGE::JUMP];
		m_aniPlayer->SetPlayFrame(5, 5, FALSE, FALSE);
		m_aniPlayer->Start();

		m_nWidth = m_aniPlayer->GetFrameWidth();
		m_nHeight = m_aniPlayer->GetFrameHeight();
		break;
	case PLAYER_STATE::LEFT_FALL:
		m_imgPlayer = m_imgPlayerList[(UINT)PLAYER_IMAGE::JUMP];
		m_aniPlayer = m_aniPlayerList[(UINT)PLAYER_IMAGE::JUMP];
		m_aniPlayer->SetPlayFrame(10, 10, TRUE, FALSE);
		m_aniPlayer->Start();

		m_nWidth = m_aniPlayer->GetFrameWidth();
		m_nHeight = m_aniPlayer->GetFrameHeight();
		break;
	case PLAYER_STATE::RIGHT_DEAD:
		m_imgPlayer = m_imgPlayerList[(UINT)PLAYER_IMAGE::DEAD];
		m_aniPlayer = m_aniPlayerList[(UINT)PLAYER_IMAGE::DEAD];
		m_aniPlayer->SetPlayFrame(0, 7, FALSE, FALSE);
		m_aniPlayer->Start();

		m_nWidth = m_aniPlayer->GetFrameWidth();
		m_nHeight = m_aniPlayer->GetFrameHeight();
		break;
	case PLAYER_STATE::LEFT_DEAD:
		m_imgPlayer = m_imgPlayerList[(UINT)PLAYER_IMAGE::DEAD];
		m_aniPlayer = m_aniPlayerList[(UINT)PLAYER_IMAGE::DEAD];
		m_aniPlayer->SetPlayFrame(8, 15, TRUE, FALSE);
		m_aniPlayer->Start();

		m_nWidth = m_aniPlayer->GetFrameWidth();
		m_nHeight = m_aniPlayer->GetFrameHeight();
		break;
	default:
		break;
	}
}