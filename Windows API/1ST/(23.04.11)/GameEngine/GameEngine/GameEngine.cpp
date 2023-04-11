// GameEngine.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "GameEngine.h"
#include "resource.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE g_hInst;                              // 현재 인스턴스입니다.
HWND      g_hWnd;                               // 윈도우 핸들
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 게임 프레임 워크 함수
void Init();
void Update(float dt);
void Render();
void Release();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAMEENGINE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEENGINE));

    MSG msg;
    memset(&msg, 0, sizeof(msg));

    Init();
    
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            static float fStartTime = (float)timeGetTime();
            float fNowTime = (float)timeGetTime();
            float fDeltaTime = (fNowTime - fStartTime) * 0.001f;

            Update(fDeltaTime);
            Render();
            fStartTime = fNowTime;
            
        }
    }

    Release();

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEENGINE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

HDC g_BackDC;
HBITMAP g_h_BackBitmap, g_hOldBackBitmap;
HBITMAP g_hPlayerBitmap;            //피카츄
RECT g_rtWindow;                    //윈도우 사이즈 저장
struct fPoint
{
    float x;
    float y;
};
POINT g_ptPlayer = { 100,100 };     //피카츄 시작위치

POINT g_ptMouse;

void Init()
{
    //더블 버퍼링을 위한 BackDC
    HDC hdc = GetDC(g_hWnd);
    g_BackDC = CreateCompatibleDC(hdc);
    GetClientRect(g_hWnd, &g_rtWindow);
    g_h_BackBitmap = CreateCompatibleBitmap(hdc, g_rtWindow.right, g_rtWindow.bottom);
    g_hOldBackBitmap = (HBITMAP)SelectObject(g_BackDC, g_h_BackBitmap);

    //피카츄 로드
    g_hPlayerBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
}

void Update(float dt)
{
    //static float fStartTime = (float)timeGetTime() * 0.001f; //고장남
    //static TCHAR szTemp[256];
    //static DWORD dwCount = 0;
    //float fNowTime = (float)timeGetTime() * 0.001f;
    //if (fNowTime - fStartTime >= 1.0f)
    //{
    //    dwCount++;
    //    wsprintf(szTemp, _T("1초마다 호출: %d"), dwCount);
    //    SetWindowText(g_hWnd, szTemp);
    //    fStartTime = fNowTime;
    //}

    /*static DWORD dwStartTick = GetTickCount64();
    static TCHAR szTemp[256];
    static DWORD dwCount = 0;
    if (GetTickCount64() - dwStartTick >= 1000)
    {
        dwCount++;
        wsprintf(szTemp, _T("1초마다 호출: %d"), dwCount);
        SetWindowText(g_hWnd, szTemp);
        dwStartTick = GetTickCount64();
    }*/
    
    static float elapsedTime = 0.0f;
    static int frameCount = 0;

    frameCount++;
    elapsedTime += dt;
    if (elapsedTime >= 1.0f)
    {
        static TCHAR szTemp[256];
        wsprintf(szTemp, _T("FPS : %d"), frameCount);
        SetWindowText(g_hWnd, szTemp);

        frameCount = 0;
        elapsedTime = 0.0f;
    }

    if (GetAsyncKeyState(VK_UP) & 0x8000)
        g_ptPlayer.y -= 100.0 * dt;
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        g_ptPlayer.y += 100.0 * dt;
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        g_ptPlayer.x -= 100.0 * dt;
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        g_ptPlayer.x += 100.0 * dt;

    GetCursorPos(&g_ptMouse);

    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
    {
        g_ptMouse.x = g_ptPlayer.x;
        g_ptMouse.y = g_ptPlayer.y;

        ClientToScreen(g_hWnd, &g_ptMouse);
        SetCursorPos(g_ptMouse.x, g_ptMouse.y);
    }
}

void Render()
{
    HDC hdc;
    hdc = GetDC(g_hWnd);
    
    FillRect(g_BackDC, &g_rtWindow, (HBRUSH)COLOR_BACKGROUND);

    //렌더
    HDC hMemDC = CreateCompatibleDC(hdc);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, g_hPlayerBitmap);
    BITMAP bit;
    GetObject(g_hPlayerBitmap, sizeof(BITMAP), &bit);
    GdiTransparentBlt(g_BackDC, g_ptPlayer.x, g_ptPlayer.y, bit.bmWidth, bit.bmHeight, hMemDC, 0, 0, bit.bmWidth, bit.bmHeight, RGB(255, 0, 255));

    TCHAR str[128];
    wsprintf(str, _T("윈도우 기준 좌표 X : %04d, Y: %04d"), g_ptMouse.x, g_ptMouse.y);
    TextOut(g_BackDC, 10, 10, str, lstrlen(str));

    ScreenToClient(g_hWnd, &g_ptMouse);
    wsprintf(str, _T("프로그램 기준 좌표 X : %04d, Y: %04d"), g_ptMouse.x, g_ptMouse.y);
    TextOut(g_BackDC, 10, 30, str, lstrlen(str));

    BitBlt(hdc, 0, 0, g_rtWindow.right, g_rtWindow.bottom, g_BackDC, 0, 0, SRCCOPY);

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);

    ReleaseDC(g_hWnd, hdc);
}

void Release()
{
    DeleteObject(g_hPlayerBitmap);
    DeleteObject(g_h_BackBitmap);
    DeleteDC(g_BackDC);
}
