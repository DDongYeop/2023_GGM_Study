#pragma once

enum class KEY_TYPE
{
	UP = VK_UP,
	DOWN = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT,
};

enum class KEY_STATE
{
	NONE,
	PRESS,
	DOWN,
	UP,
	END,
};

enum
{
	KEY_TYPE_COUNT = static_cast<int>(UINT8_MAX + 1),
	KEY_STATE_COUNT = static_cast<int>(KEY_STATE::END),
};

class Input
{
public:
	Input();
	~Input();

public:
	void Init(HWND hWnd);
	void Update();

public:
	bool GetButton(KEY_TYPE key) { return GetState(key) == KEY_STATE::PRESS; }
	bool GetButtonDown(KEY_TYPE key) { return GetState(key) == KEY_STATE::DOWN; }
	bool GetButtonUp(KEY_TYPE key) { return GetState(key) == KEY_STATE::UP; }

	const POINT& GetMousePos() { return m_mousePos; }

private:
	inline KEY_STATE GetState(KEY_TYPE key) { return m_states[static_cast<UINT8>(key)]; }

private:
	HWND				m_hWnd;
	vector<KEY_STATE>	m_states;
	POINT				m_mousePos = {};
};

