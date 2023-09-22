#pragma once
class BaseWindow
{
public:
	BaseWindow();
	~BaseWindow();

	//�� ��� �����ϴ°�
	//1.�ν��Ͻ�, ������ �ڵ�

	//���漱��� 3���� 
	int					Run(HINSTANCE _hInst, LPWSTR _lpCmdline, int _nCmdShow);
	ATOM                MyRegisterClass();
	//BOOL                InitInstance(HINSTANCE, int);
	void				WindowCreate();
	void				WindowShow(int _nCmdShow);
	void				WindowUpdate();
	LRESULT CALLBACK    WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
	int					MessageLoop();

private:
	HWND		m_hWnd;
	HINSTANCE	m_hInst;
};

