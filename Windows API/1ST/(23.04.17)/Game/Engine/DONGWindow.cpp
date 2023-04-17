#include "pch.h"
#include "DONGWindow.h"

DONGWindow::DONGWindow() : m_hWnd(NULL), m_hInstance(NULL)
{
	m_nWidth = SCREEN_WIDTH;
	m_nHeight = SCREEN_HEIGHT;
}

DONGWindow::~DONGWindow()
{
}

int DONGWindow::Run(HINSTANCE hInst, LPWSTR lpCmdLine, int nCmdShow)
{
	m_hInstance = hInst;

	registerWndClass();
	createWindow();
	showWindow(nCmdShow);

	return messageLoop();
}

LRESULT DONGWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void DONGWindow::registerWndClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= DONGWindow::WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= m_hInstance;
	wcex.hIcon			= LoadIcon(m_hInstance, IDI_APPLICATION);
	wcex.hCursor		= LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	= nullptr;
	wcex.lpszClassName	= _T("DONG FRAMEWORK");
	wcex.hIconSm		= LoadIcon(m_hInstance, IDI_APPLICATION);

	RegisterClassExW(&wcex);
}

void DONGWindow::createWindow()
{
	m_hWnd = CreateWindowW(_T("DONG FRAMEWORK"), _T("DONG"), WS_OVERLAPPEDWINDOW, 100, 100, m_nWidth, m_nHeight, nullptr, nullptr, m_hInstance, nullptr);
}

void DONGWindow::showWindow(int nCmdShow)
{
	ShowWindow(m_hWnd, nCmdShow);
}

int DONGWindow::messageLoop()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	
	Startup();

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			MainUpdate();
			MainRender();
		}
	}
	Cleanup();

	return (int)msg.wParam;
}
