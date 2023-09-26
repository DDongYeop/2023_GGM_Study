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
private:
	void Update();
	void Render();
private:
	HWND	m_hWnd;
	HDC		m_hDC;
	POINT	m_ptResolition;
	Object	m_obj;
};

