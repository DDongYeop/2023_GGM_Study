#pragma once
class BaseWindow
{
public:
	BaseWindow();
	~BaseWindow();

	//꼭 들고 가야하는거
	//1.인스턴스, 윈도우 핸들

	//전방선언된 3가지 
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

