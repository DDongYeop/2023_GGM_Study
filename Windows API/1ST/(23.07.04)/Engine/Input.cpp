#include "pch.h"
#include "Input.h"

Input::Input()
{
}

Input::~Input()
{
}

void Input::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	m_states.resize(KEY_TYPE_COUNT, KEY_STATE::NONE);
}

void Input::Update()
{
	HWND hwnd = ::GetActiveWindow();
	if (m_hWnd != hwnd)
	{
		for (UINT key = 0; key < KEY_TYPE_COUNT; ++key)
			m_states[key] = KEY_STATE::NONE;
		return;
	}

	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(asciiKeys) == false)
		return;

	for (UINT key = 0; key < KEY_TYPE_COUNT; ++key)
	{
		if (asciiKeys[key] & 0x80)
		{
			KEY_STATE& state = m_states[key];

			// 이전 프레임에 키를 누른 상태인지 체크해보자.
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
				state = KEY_STATE::PRESS;
			else
				state = KEY_STATE::DOWN;
		}
		else
		{
			KEY_STATE& state = m_states[key];

			// 이전 프레임에 키를 누른 상태인지 체크
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
				state = KEY_STATE::UP;
			else
				state = KEY_STATE::NONE;
		}
	}

	::GetCursorPos(&m_mousePos);
	::ScreenToClient(m_hWnd, &m_mousePos);
}
