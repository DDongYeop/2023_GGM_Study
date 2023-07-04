#pragma once
#include "Pawn.h"

#define VELOCITY	500
#define GRAVITY		-1000

enum class PLAYER_IMAGE
{
	IDLE,
	MOVE,
	JUMP,
	DEAD,
	COUNT
};

enum class PLAYER_STATE
{
	// IDLE
	RIGHT_IDLE,
	LEFT_IDLE,

	// MOVE
	RIGHT_MOVE,
	LEFT_MOVE,

	// JUMP
	RIGHT_JUMP,
	LEFT_JUMP,

	// FALL
	RIGHT_FALL,
	LEFT_FALL,

	// DEAD
	RIGHT_DEAD,
	LEFT_DEAD,

	COUNT
};

class Player : public Pawn, public enable_shared_from_this<Player>
{
public:
	Player();
	Player(float x, float y, int width = 0, int height = 0, float scale = 1.0f, float speed = 100.0f);
	virtual ~Player();

public:
	void	Init() override;
	void	Update(float dt) override;
	void	Render(HDC hdc) override;
	void	Release() override;

public:
	void	SetAnimation(PLAYER_STATE state);

	bool	IsOnGround() { return m_isGround; }
	void	SetGround(bool ground) { m_isGround = ground; }

	bool	GetCanMoveRight() { return m_canMoveRight; }
	void	SetCanMoveRight(bool canMove) { m_canMoveRight = canMove; }

	bool	GetCanMoveLeft() { return m_canMoveLeft; }
	void	SetCanMoveLeft(bool canMove) { m_canMoveLeft = canMove; }

	bool	IsRight() { return (UINT)m_state % 2 == 0; }
	bool	IsLeft() { return (UINT)m_state % 2 == 1; }

	bool	IsMovingLeft()
	{
		if (m_isMoving && IsLeft())
			return true;
		return false;
	}

	bool	IsMovingRight()
	{
		if (m_isMoving && IsRight())
			return true;
		return false;
	}

	bool	IsJumping()
	{
		if (m_state == PLAYER_STATE::LEFT_JUMP || m_state == PLAYER_STATE::RIGHT_JUMP)
			return true;
		return false;
	}

	bool	IsFalling()
	{
		if (m_state == PLAYER_STATE::LEFT_FALL || m_state == PLAYER_STATE::RIGHT_FALL)
			return true;
		return false;
	}

	void	SetPos(float x, float y) { m_fPosX = x; m_fPosY = y; }

private:
	PLAYER_STATE	m_state;
	PLAYER_STATE	m_beforeState;

	bool			m_isGround;
	bool			m_canMoveRight;
	bool			m_canMoveLeft;

	bool			m_isMoving;

	float			m_gravity;
	float			m_velocity;

private:
	shared_ptr<Image>				m_imgPlayer;
	vector<shared_ptr<Image>>		m_imgPlayerList;

	shared_ptr<Animation>			m_aniPlayer;
	vector<shared_ptr<Animation>>	m_aniPlayerList;
};

