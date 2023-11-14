#include "pch.h"
#include "BaseWindow.h"
#include "Resource.h"
#include "Core.h"
BaseWindow::BaseWindow(POINT _ptResolution)
	: m_hWnd(0)
	, m_hInst(0)
    , m_ptResolution(_ptResolution)
{
}

BaseWindow::~BaseWindow()
{
}

int BaseWindow::Run(HINSTANCE _hInst, LPWSTR _lpCmdline, int _nCmdShow)
{
    //this->m_hWnd;
    m_hInst = _hInst;
    this->MyRegisterClass();
    this->WindowCreate();
    this->WindowShow(_nCmdShow);
    this->WindowUpdate();
    // Init();
    if (!Core::GetInst()->Init(m_hWnd, m_ptResolution))
    {
        MessageBox(m_hWnd, L"Core 초기화 실패", L"FAIL", MB_OK);
    }
    return this->MessageLoop();
}

ATOM BaseWindow::MyRegisterClass()
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = BaseWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInst;
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_MY2023WINAPIFRAMEWORK22));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = WINDOW_CLASS_NAME;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

void BaseWindow::WindowCreate()
{
    int iWinposx = GetSystemMetrics(SM_CXSCREEN) / 2 - m_ptResolution.x / 2;
    int iWinposy = GetSystemMetrics(SM_CYSCREEN) / 2 - m_ptResolution.y / 2;
    
    m_hWnd = CreateWindowW(WINDOW_CLASS_NAME, L"Jun's Framework", WS_OVERLAPPEDWINDOW,
        iWinposx, iWinposy, m_ptResolution.x, m_ptResolution.y, nullptr, nullptr, m_hInst, nullptr);
    
    RECT rt = { iWinposx, iWinposy, iWinposx + m_ptResolution.x, iWinposy + m_ptResolution.y };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
    MoveWindow(m_hWnd, iWinposx, iWinposy, rt.right - rt.left, rt.bottom - rt.top, true);
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
    //    // 우리가 PAINT를 쓸까..?
    //case WM_PAINT:
    //{
    //    PAINTSTRUCT ps;
    //    HDC hdc = BeginPaint(_hWnd, &ps);
    //    // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
    //    Rectangle(hdc, 10, 10, 110, 110);
    //    EndPaint(_hWnd, &ps);
    //}
    //break;
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
    // 기본 메시지 루프입니다:
    while (true)
    {
        // 어? 메시지 있네? 그럼 여기 ㅇㅋ
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // 어? 메시지 없음? ㅇㅋ 나 따로놈 게임함
            Core::GetInst()->GameLoop();
        }
    }
    Core::GetInst()->Release();
    return (int)msg.wParam;
}
