#pragma once
//�ϳ��� ��𼭵� �� �� �ֵ���
//1�б⿡ �ߴ� �̱��� : ���̳��� �̱��� = �����Ҵ�
//  ���� : �������� �ʴ��� �ٽ� ���� ����
//  ���� : �������� �Ҵ��ϱ⿡ ���͸� ������Ѵ�.
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
	const HDC& GetMainDC() const { return m_hDC; }
	const HWND& GetHwnd() const { return m_hWnd; };
	const POINT& GetResolution() const { return m_ptResolition; }
private:
	void Update();
	void Render();
private:
	HWND	m_hWnd;
	HDC		m_hDC; //���� DC
	HDC		m_hbackDC; //�� ���� DC
	HBITMAP m_hbackbit; //�� ���ۿ� �׸� ��Ʈ��
	POINT	m_ptResolition;
};

