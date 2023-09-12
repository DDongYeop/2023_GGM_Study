﻿// (23.09.05).winapi.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "(23.09.05).winapi.h"
#include <math.h>
#include <string>

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
    LoadStringW(hInstance, IDC_MY230905WINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY230905WINAPI));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY230905WINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY230905WINAPI);
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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    static POINT ptObjpos = { 500,500 };
    static POINT ptObjscale = { 100,100 };
    static RECT rectview;

    static float textPosX = 100, textPosY = 100;
    static float namePosX = 0, namePosY = 0;
    static float mousePosX = 0, mousePosY = 0;

    static std::wstring ggmStr = L"겜마고";
    static std::wstring nameStr = L"경동엽";

    static bool isKeydown;
    static bool isGoing = false;
    static bool isNamePrint = false;
    static bool isclick = false;

    switch (message)
    {
    case WM_SIZE:
        GetClientRect(hWnd, &rectview);
        break;
    case WM_CREATE:
        GetClientRect(hWnd, &rectview);
        break;
    case WM_LBUTTONDOWN:
    {
        /*int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        int disance = sqrt(pow(50 - x, 2) + pow(50 - y, 2));
        if (disance < 50)
        {
            isRect = true;
            InvalidateRect(hWnd, nullptr, true);
        }*/

        //겜프 과제
        /*namePosX = LOWORD(lParam);
        namePosY = HIWORD(lParam);
        isNamePrint = true;
        InvalidateRect(hWnd, nullptr, true);
        SetTimer(hWnd, 1, 100, nullptr);*/

        //2-3-5
        /*mousePosX = LOWORD(lParam);
        mousePosY = HIWORD(lParam);
        isclick = true;*/
        //InvalidateRect(hWnd, nullptr, true);
    } break;
    case WM_LBUTTONDBLCLK:
    {
        //2-3-5
        //InvalidateRect(hWnd, nullptr, true);
    }break;
    case WM_MOUSEMOVE:
        //2-3-5
        //2-3-5
        /*if (isclick)
        {
            hdc = GetDC(hWnd);
            MoveToEx(hdc, mousePosX, mousePosY, nullptr);
            mousePosX = LOWORD(lParam);
            mousePosY = HIWORD(lParam);
            LineTo(hdc, mousePosX, mousePosY);
            ReleaseDC(hWnd, hdc);
        }*/
        break;
    case WM_LBUTTONUP:
        //겜프 과제
        /*isNamePrint = false;
        InvalidateRect(hWnd, nullptr, true);*/

        //2-3-7
        isclick = false;
        break;
    case WM_TIMER:
        /*if (ptObjpos.x + ptObjscale.x / 2 + 10 < rectview.right)
            ptObjpos.x += 10;
        InvalidateRect(hWnd, nullptr, true);*/

        //겜프 과제
        /*if (isNamePrint)
        {
            textPosX += (namePosX - textPosX) / 100.f;
            textPosY += (namePosY - textPosY) / 100.f;
            InvalidateRect(hWnd, nullptr, true);
        }*/
        break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_RETURN:
        {
            /*isGoing = !isGoing;
            if (isGoing)
                SetTimer(hWnd, 1, 100, nullptr);
            else
                KillTimer(hWnd, 1);*/
        }break;
        case VK_LEFT:
            //ptObjpos.x -= 10;
            break;
            // 오른쪽키를 누르는데 밖에 못빠져나가게 해봐.
        case VK_RIGHT:
        {
            /*SetTimer(hWnd, 1, 100, nullptr);
            isKeydown = true;
            break;*/
        }
        }
    } break;
    case WM_KEYUP:
        //겜프 과제
        /*isKeydown = false;
        InvalidateRect(hWnd, nullptr, true);*/
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hWnd, &ps);
        /*HBRUSH hBluebrush = CreateSolidBrush(RGB(0, 0, 255));
        HBRUSH hDefaultbrush = CreateSolidBrush(RGB(255, 255, 255));
        if (isKeydown)
            SelectObject(hdc, hBluebrush);
        else
            SelectObject(hdc, hDefaultbrush);*/
        /*Rectangle(hdc, 0, 0, 600, 600);
        Ellipse(hdc
            , ptObjpos.x - ptObjscale.x / 2
            , ptObjpos.y - ptObjscale.y / 2
            , ptObjpos.x + ptObjscale.x / 2
            , ptObjpos.y + ptObjscale.y / 2);*/

        /*Ellipse(hdc, 0, 0, 100, 100);
        if (isRect)
            Rectangle(hdc, 0, 0, 100, 100);*/
        
        //겜프 과제
        /*TextOut(hdc, textPosX, textPosY, ggmStr.c_str(), ggmStr.length());
        if(isNamePrint)
            TextOut(hdc, namePosX, namePosY, nameStr.c_str(), nameStr.length());*/

        //2-3-5
        //SetPixel(hdc, mousePosX, mousePosY, RGB(255, 255, 255));

        //2-3-6
        std::wstring wstr = L"겜프 재밋당";
        TextOut(hdc, rectview.right / 2, rectview.bottom / 2, wstr.c_str(), wstr.length());

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        KillTimer(hWnd, 1);
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
