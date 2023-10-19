#pragma once
//하나만 어디서든 쓸 수 있도록
//1학기에 했던 싱글톤 : 다이나믹 싱글톤 = 동적할당
//  장점 : 존재하지 않더라도 다시 생성 가능
//  단점 : 동적으로 할당하기에 제귀를 해줘야한다.
#include "define.h"
#include "Object.h"

class Core
{
	SINGLE(Core);
public:
	bool Init(HWND _hWnd, POINT _ptResolition);
	void GameLoop();
	void Release();
public:
	const HWND& GetHwnd() const { return m_hWnd; };
private:
	void Update();
	void Render();
private:
	HWND	m_hWnd;
	HDC		m_hDC; //메인 DC
	HDC		m_hbackDC; //백 버퍼 DC
	HBITMAP m_hbackbit; //백 버퍼에 그릴 비트맵
	POINT	m_ptResolition;
};

