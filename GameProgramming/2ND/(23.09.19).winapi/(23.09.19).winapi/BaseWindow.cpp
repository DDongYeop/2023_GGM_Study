#include "pch.h"
#include "BaseWindow.h"
#include "Resource.h"

BaseWindow::BaseWindow() : m_hWnd(0), m_hInst(0)
{
}

BaseWindow::~BaseWindow()
{
}

int BaseWindow::Run(HINSTANCE _hInst, LPWSTR _lpCmdline, int _nCmdShow)
{
    return 0;
}

ATOM BaseWindow::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc; //다음주에 설명 | 베네핏 준비해둬라
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInst;
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_MY230919WINAPI));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY230919WINAPI);
    wcex.lpszClassName = WINDOW_CLASS_NAME;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

void BaseWindow::WindowCreate()
{

    m_hWnd = CreateWindowW(WINDOW_CLASS_NAME, L"dong's Framework", 
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);
}

void BaseWindow::WindowShow(int _nCmdShow)
{
    ShowWindow(m_hWnd, _nCmdShow);
}

void BaseWindow::WindowUpdate()
{
    UpdateWindow(m_hWnd);
}

LRESULT BaseWindow::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
        //우리가 PAINT를 쓸까?
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(_hWnd, &ps);

        EndPaint(_hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }
    return 0;
}

int BaseWindow::MessageLoop()
{
    MSG msg;
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {

        }
    }

    return (int)msg.wParam;
}
