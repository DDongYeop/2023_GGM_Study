// (23.09.12).winapi.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "(23.09.12).winapi.h"
#include <vector>
#include <time.h>
#include <algorithm> 

#define MAX_LOADSTRING 100
#define WINSIZEX 1280
#define WINSIZEY 720
#define RECT_RENDER(posx, posy, scalex, scaley) Rectangle(hdc, posx-scalex/2, posy-scaley/2, posx+scalex/2, posy+scaley/2)
#define RECT_MAKE(posx, posy, scalex, scaley) {posx-scalex/2, posy-scaley/2, posx+scalex/2, posy+scaley/2}

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
    LoadStringW(hInstance, IDC_MY230912WINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY230912WINAPI));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY230912WINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY230912WINAPI);
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
      CW_USEDEFAULT, 0, WINSIZEX, WINSIZEY, nullptr, nullptr, hInstance, nullptr);

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

struct tObjInfo
{
    POINT pos;
    POINT scale;
};

enum class MOVE_DIR
{
    LEFT, RIGHT, UP, DOWN
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static RECT rectview;
    static std::vector<tObjInfo> vecObj;
    static tObjInfo player = { {600, 600}, {100, 100} };
    static float fMoveSpeed = 20.f;
    static int iDelay = 0;
    /*static tObjInfo obj = { {500, 100}, {100, 100} };
    static MOVE_DIR eMoveDir;*/

    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 1, 10, nullptr);
        GetClientRect(hWnd, &rectview);
        srand((unsigned int)time(nullptr));
        break;
    case WM_TIMER:
    {
        //내가 가진 vector에 obj 넣기
        if (iDelay >= 50)
        {
            tObjInfo tempinfo;
            tempinfo.pos.x = rand() % rectview.right;
            tempinfo.pos.y = 0;
            tempinfo.scale.x = 50;
            tempinfo.scale.y = 50;
            vecObj.push_back(tempinfo);
            iDelay = rand() % 50;
        }
        else
            iDelay++;

        std::vector<tObjInfo>::iterator iter = vecObj.begin();
        RECT temprt, playerrt, object;
        playerrt = RECT_MAKE(player.pos.x, player.pos.y, player.scale.x, player.scale.y);
        for (; iter != vecObj.end();)
        {
            iter->pos.y += 10;
            object = RECT_MAKE(iter->pos.x, iter->pos.y, iter->scale.x, iter->scale.y);
            if (iter->pos.y > WINSIZEX || IntersectRect(&temprt, &playerrt, &object))
                iter = vecObj.erase(iter);
            else
                ++iter;
        }

        InvalidateRect(hWnd, nullptr, true);
    } break;
    case WM_KEYDOWN:
    {
        //충돌연습
        /*if (wParam == VK_RIGHT)
        {
            player.pos.x += fMoveSpeed;
            eMoveDir = MOVE_DIR::RIGHT;
            RECT temprt;
            RECT playerrt, objrt;
            playerrt = RECT_MAKE(player.pos.x, player.pos.y, player.scale.x, player.scale.y);
            objrt = RECT_MAKE(obj.pos.x, obj.pos.y, obj.scale.x, obj.scale.y);

            if (IntersectRect(&temprt, &playerrt, &objrt) && eMoveDir == MOVE_DIR::RIGHT)
            {
                obj.pos.x += fMoveSpeed;
            }
        }
        InvalidateRect(hWnd, nullptr, true);*/

        switch (wParam)
        {
        case 'A':
        case VK_LEFT:
            player.pos.x -= 10;
            if (player.pos.x <= 0)
                player.pos.x = 0;
            break;
        case 'D':
        case VK_RIGHT:
            player.pos.x += 10;
            if (player.pos.x >= WINSIZEX)
                player.pos.x = WINSIZEX;
            break;
        default:
            break;
        }

    } break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        //충돌연습
        //RECT_RENDER(player.pos.x, player.pos.y, player.scale.x, player.scale.y);
        /*RECT_RENDER(obj.pos.x, obj.pos.y, obj.scale.x, obj.scale.y);*/

        HBRUSH hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
        HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hGreenBrush);
        RECT_RENDER(player.pos.x, player.pos.y, player.scale.x, player.scale.y);
        SelectObject(hdc, hDefaultBrush);
        for (size_t i = 0; i < vecObj.size(); ++i)
            RECT_RENDER(vecObj[i].pos.x, vecObj[i].pos.y, vecObj[i].scale.x, vecObj[i].scale.y);

        DeleteObject(hGreenBrush);

        EndPaint(hWnd, &ps);
    } break;
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
