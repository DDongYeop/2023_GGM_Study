#pragma once

enum class KEY_STATE
{
	// NONE:안눌림
	// DOWN:딱 눌림
	// UP:뗌
	// PRESS:누르는증
	NONE, DOWN, UP, PRESS
};

enum class KEY_TYPE
{
	LEFT, RIGHT, UP, DOWN,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,
	CTRL, LALT, LSHIFT, SPACE,
	ENTER, TAB, ESC, LBUTTON, RBUTTON, LAST
	// LAST의미: 끝이라는 뜻임
};

enum class OBJECT_GROUP
{
	DEFAULT,
	PLAYER,
	BULLET,
	MONSTER,
	END = 30
};
