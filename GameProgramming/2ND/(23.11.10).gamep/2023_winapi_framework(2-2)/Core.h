#pragma once
// 하나만, 어디서든 쓸수있어야함.
// 싱글톤을 구현하는 방법이 엄청 많음
// 1학기때 했던걸 다이나믹 싱글톤 = 동적할당
// 장점: 존재하지 않더라도 다시 생성할 수 있다.
// 단점: 동적으로 할당하기에 제거를 해줘야한다.
//private:
//	static Core* m_pInst;
//public:
//	static Core* GetInst()
//	{
//		if (m_pInst == nullptr)
//			m_pInst = new Core;
//		return m_pInst;
//	}
//public:
//	static void DestroyInst()
//	{
//		SAFE_DELETE(m_pInst);

// 정적(static)할당.
#include "define.h"
#include "Object.h"
class Core
{
	SINGLE(Core);
public:
	bool Init(HWND _hwnd, POINT _ptResolution);
	void GameLoop();
	void Release();
public:
	const HWND& GetHwnd() const { return m_hWnd; }
	const POINT& GetResolution() const 
	{ return m_ptResolution; }
	const HDC& GetMainDC() const
	{
		return m_hDC;
	}
	const HBRUSH& GetBrush(BRUSH_TYPE _eType)
	{
		return m_arrBrush[(UINT)_eType];
	}
	const HPEN& GetPen(PEN_TYPE _eType)
	{
		return m_arrPen[(UINT)_eType];
	}
private:
	void Update();
	void Render();
	void CreateGDI();
private:
	HWND	m_hWnd;
	HDC		m_hDC; // 메인 DC
	HDC		m_hbackDC; // 백 버퍼 DC
	HBITMAP	m_hbackbit; // 백 버퍼에 그릴 비트맵
	POINT	m_ptResolution; // 해상도
	HBRUSH  m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN    m_arrPen[(UINT)PEN_TYPE::END];

//public:
//	static Core* GetInst()
//	{
//		static Core m_pInst;
//		return &m_pInst;
//	}
//private:
//	Core();
//	~Core();
};

