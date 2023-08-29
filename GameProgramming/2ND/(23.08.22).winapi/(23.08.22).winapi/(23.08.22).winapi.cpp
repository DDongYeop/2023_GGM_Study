// (23.08.22).winapi.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h" // window.h << WinAPT에 iostream (안에 들어있음)
#include "(23.08.22).winapi.h"
#include <string>

using namespace std;

#define MAX_LOADSTRING 100
#define PROGRAM_TITLE L"동엽의 윈도우" //제목 수정을 위한 define
#define WINSIZEX 1280
#define WINSIZEY 720

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING] = PROGRAM_TITLE;                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다: //전방선언 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // 지금 켜둔거
                     _In_opt_ HINSTANCE hPrevInstance, // 사용안함 프리뷰인스턴스 가상메모리가 알아서 함
                     _In_ LPWSTR    lpCmdLine, // 겜 개발에서 안 쓸 예정
                     _In_ int       nCmdShow) // 겜 개발에서 안 쓸 예정
{
    UNREFERENCED_PARAMETER(hPrevInstance); // 이거 안 써요 (라고 써있다고 보면 된다)
    UNREFERENCED_PARAMETER(lpCmdLine); // 이거 안 써요 (라고 써있다고 보면 된다)

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); //제목 지정, 지워야 반영된다 
    LoadStringW(hInstance, IDC_MY230822WINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance); // 이제 시작 

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY230822WINAPI));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS/*더블클릭 감지*/;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY230822WINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_CROSS);
    //wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+2);
    wcex.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY230822WINAPI);
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

   int screenX = (GetSystemMetrics(SM_CXSCREEN) * 0.5f) - (WINSIZEX * 0.5f);
   int screenY = (GetSystemMetrics(SM_CYSCREEN) * 0.5f) - (WINSIZEY * 0.5f);

   HWND hWnd = CreateWindowW(szWindowClass, szTitle/* 이거가 이름 바꿔주는거 L"" */, WS_OVERLAPPEDWINDOW | WS_HSCROLL,
       screenX, screenY, WINSIZEX, WINSIZEY, nullptr, nullptr, hInstance, nullptr);

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
    static UINT iCount = 0; 
    static char strArr[10];

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            
            //사각형
            //Rectangle(hdc, 10, 10, 110, 110);
            //Ellipse(hdc, 50, 50, 150, 150);

            //텍스트 출력
            //wstring wstr = L"2강 시작";
            /*LPCWSTR;
            TextOut(hdc, 10, 10, wstr.c_str(), wstr.length());*/
            // DrawText
            /*RECT rt = {50, 50, 100, 100};
            Rectangle(hdc, 50, 50, 100, 100);
            DrawText(hdc, wstr.c_str(), wstr.length(), &rt, DT_CENTER | DT_NOCLIP);*/

            //점 출력 
            /*for (int i = 0; i < 1000; ++i)
                SetPixel(hdc, rand() % 100, rand() % 100, RGB(255, 0, 0));*/

            //선 출력 
            /*for (int i = 0; i <= 1280; i += 1280 / 16)
            {
                MoveToEx(hdc, i, 0, nullptr);
                LineTo(hdc, i, 720);
            }
            for (int i = 0; i <= 720; i += 720 / 9)
            {
                MoveToEx(hdc, 0, i, nullptr);
                LineTo(hdc, 1280, i);
            }*/

            //연습 문제 2
            for (int i = 100; i <= 450; i += 70)
            {
                 
            }


            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        //_itoa_s(iCount, strArr, 10);
        //MessageBoxA(hWnd, strArr, "DESTROY", MB_OK);
        //MessageBox(hWnd, L"X버튼 감지", L"DESTORY", MB_OK);
        PostQuitMessage(0);
        break;
    case WM_LBUTTONDBLCLK:
        MessageBox(hWnd, L"마우스 왼쪽 버튼 더블 클릭", L"메세지 박스", MB_OK | MB_ICONERROR);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    ++iCount;
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
