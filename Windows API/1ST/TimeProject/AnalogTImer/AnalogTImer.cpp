// AnalogTImer.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "AnalogTImer.h"
#include <math.h>

#define PI 3.14
#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_ANALOGTIMER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ANALOGTIMER));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ANALOGTIMER));
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
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       0, 0, 400, 400, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

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

int g_nRadius;
int g_nWidth;
int g_nHeight;
SYSTEMTIME g_stTimer;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        SetTimer(hWnd, 1, 1000, nullptr);
        RECT rt;
        GetClientRect(hWnd, &rt);
        g_nWidth = rt.right - rt.left;
        g_nHeight = rt.bottom - rt.top;
        g_nRadius = ((g_nWidth > g_nHeight) ? g_nHeight : g_nWidth) * 9 / 20;
    }
        break;
    case WM_TIMER:
        InvalidateRect(hWnd, nullptr, true);
        break;
    case WM_PAINT:
        {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

        double x, y;
        RECT rt;

        for (int i = 0; i < 12; i++)
        {
            x = g_nWidth / 2 + sin(2 * PI / 12 * i) * g_nRadius;
            y = g_nHeight / 2 - cos(2 * PI / 12 * i) * g_nRadius;

            rt.left = x - 4;
            rt.right = x + 4;
            rt.top = y - 4;
            rt.bottom = y + 4;

            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
            HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

            FillRect(hdc, &rt, hBlueBrush);
            SelectObject(hdc, hOldBrush);
            DeleteObject(hBlueBrush);
            
            SYSTEMTIME st;
            GetLocalTime(&st);

            //시침 
            HPEN hPen = CreatePen(PS_SOLID, 16, RGB(255, 0, 0));
            HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
            x = sin(2 * PI * (st.wHour * 60 + st.wMinute) / 720);
            y = -cos(2 * PI * (st.wHour * 60 + st.wMinute) / 720);
            MoveToEx(hdc, (g_nWidth / 2) - x * g_nRadius / 10, (g_nHeight / 2) - y * g_nRadius / 10, nullptr);
            LineTo(hdc, (g_nWidth / 2) + x * g_nRadius / 2, (g_nHeight / 2) + y * g_nRadius / 2);
            SelectObject(hdc, hOldPen);
            DeleteObject(hPen);

            //분침
            hPen = CreatePen(PS_SOLID, 9, RGB(0, 255, 0));
            hOldPen = (HPEN)SelectObject(hdc, hPen);
            x = sin(2 * PI * st.wMinute / 60);
            y = -cos(2 * PI * st.wMinute / 60);
            MoveToEx(hdc, (g_nWidth / 2) - x * g_nRadius / 10, (g_nHeight / 2) - y * g_nRadius / 10, nullptr);
            LineTo(hdc, (g_nWidth / 2) + x * g_nRadius * 2/3, (g_nHeight / 2) + y * g_nRadius * 2/3);
            SelectObject(hdc, hOldPen);
            DeleteObject(hPen);

            //초침
            hPen = CreatePen(PS_SOLID, 9, RGB(0, 0, 255));
            hOldPen = (HPEN)SelectObject(hdc, hPen);
            x = sin(2 * PI * st.wSecond / 60);
            y = -cos(2 * PI * st.wSecond / 60);
            MoveToEx(hdc, (g_nWidth / 2) - x * g_nRadius / 10, (g_nHeight / 2) - y * g_nRadius / 10, nullptr);
            LineTo(hdc, (g_nWidth / 2) + x * g_nRadius, (g_nHeight / 2) + y * g_nRadius);
            SelectObject(hdc, hOldPen);
            DeleteObject(hPen);

            // 정각이 다가왔을 떄 비프음 울리기
            if (st.wSecond >= 57 && st.wSecond <= 59)
                Beep(500, 200);
            else if (st.wSecond == 0)
                Beep(1000, 400);
        }
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

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
