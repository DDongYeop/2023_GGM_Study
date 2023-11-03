#pragma once
class BaseWindow
{
public:
	BaseWindow(POINT _ptResolution);
	~BaseWindow();
	// 내가 이거는 꼭 멤버변수로 들고가야한다!
	// 1. 인스턴스, 윈도우 핸들
	int					Run(HINSTANCE _hInst, LPWSTR _lpCmdline, int _nCmdShow);
	ATOM                MyRegisterClass();
//	BOOL                InitInstance(HINSTANCE, int);
	void				WindowCreate();
	void				WindowShow(int _nCmdShow);
	void				WindowUpdate();
	static LRESULT CALLBACK    WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
	int				    MessageLoop();
private:
	HWND		m_hWnd;
	HINSTANCE	m_hInst;
	POINT		m_ptResolution;
};

