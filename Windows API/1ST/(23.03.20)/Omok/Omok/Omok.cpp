// Omok.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Omok.h"

#define MAX_LOADSTRING 100

// Omok Define
#define WIN_WIDTH   590
#define WIN_HEIGHT  600

#define X_COUNT     19
#define Y_COUNT     19

#define START_X     50
#define START_Y     50

#define DOL_SIZE    26
#define DOL_RADIUS  DOL_SIZE/2

//좌표상에서 돌의 위치
#define XPOS(x) (START_X + (x) * DOL_SIZE)
#define YPOS(y) (START_Y + (y) * DOL_SIZE)

// Omok Enum 
// OMOKDOL (NONE: 아무것도 놓이지 않은 상태, BLACK: 흑돌, WHITE: 백돌)
enum OMOKDOL { NONE = 0, BLACK = 1, WHITE = 2 };

enum GAMESTATE { READY=0, BLACK_WIN, WHITE_WIN, TIE_GAME };
const WCHAR* GAMESTATE_STR[] = { _T("READY"), _T("BLACK_WIN"), _T("WHITE_WIN"), _T("TIE_GAME") };

// Omok Variables
BYTE g_omokBoard[Y_COUNT][X_COUNT];
bool g_turn = true;     // true: 흑돌, false: 백돌
int g_count = 0;

GAMESTATE g_gameState = GAMESTATE::READY;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Omok Function 
void OnReset(HWND hWnd);
void OnPaint(HWND hWnd);
void ONLButtonDown(HWND hWnd, int x, int y);

bool five_Check(OMOKDOL dol, int dy, int dx, int y, int x);
GAMESTATE IsGameOver();

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
    LoadStringW(hInstance, IDC_OMOK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OMOK));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OMOK));
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
      100, 100, WIN_WIDTH, WIN_HEIGHT, 0, nullptr, nullptr, hInstance, nullptr);

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
    switch (message)
    {
    case WM_CREATE:
    {
        OnReset(hWnd);
    } break;
    case WM_LBUTTONDOWN:
    {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        ONLButtonDown(hWnd, x, y);

        GAMESTATE result = IsGameOver();
        switch (result)
        {
        case READY:
            break;
        case BLACK_WIN:
        case WHITE_WIN:
        case TIE_GAME:
        {
            WCHAR str[100];
            wsprintf(str, _T("WIN : %s"), GAMESTATE_STR[result]);
            if (MessageBox(hWnd, str, _T("Omok"), MB_YESNO) == IDYES)
                OnReset(hWnd);
        }break;
        default:
            break;
        }
    } break;
    case WM_PAINT:
    {
        OnPaint(hWnd);
    } break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void OnReset(HWND hWnd)
{
    for (int y = 0; y < Y_COUNT; ++y)
    {
        for (int x = 0; x < X_COUNT; ++x)
        {
            g_omokBoard[y][x] = OMOKDOL::NONE;
        }
    }

    //흑돌 우선
    g_turn = true;

    //게임 상태 : READY
    g_gameState = GAMESTATE::READY;

    InvalidateRect(hWnd, nullptr, true);
}

void OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    RECT bgRect; 
    bgRect.left = START_X;
    bgRect.top = START_Y;
    bgRect.right = bgRect.left + (X_COUNT - 1) * DOL_SIZE;
    bgRect.bottom = bgRect.top + (Y_COUNT - 1) * DOL_SIZE;

    // 배경색 브러쉬 설정
    HBRUSH bgBrush = CreateSolidBrush(RGB(244, 176, 77));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, bgBrush);

    Rectangle(hdc, bgRect.left, bgRect.top, bgRect.right, bgRect.bottom);
    SelectObject(hdc, oldBrush);
    DeleteObject(bgBrush);

    //세로 선 
    for (int x = 1; x < X_COUNT - 1; ++x)
    {
        MoveToEx(hdc, XPOS(x), YPOS(0), nullptr);
        LineTo(hdc, XPOS(x), YPOS(Y_COUNT - 1));
    }
    //가로 선
    for (int y = 1; y < Y_COUNT - 1; ++y)
    {
        MoveToEx(hdc, XPOS(0), YPOS(y), nullptr);
        LineTo(hdc, XPOS(X_COUNT - 1), YPOS(y));
    }

    //현재 놓아야할 돌 선택 
    SelectObject(hdc, GetStockObject(LTGRAY_BRUSH));
    int outline = 3;

    // 흑돌의 아웃라인 
    if (g_turn)
    {
        Ellipse(hdc, WIN_WIDTH / 2 - DOL_SIZE * 2 - DOL_RADIUS - outline, START_Y / 2 - DOL_RADIUS - outline, 
                     WIN_WIDTH / 2 - DOL_SIZE * 2 + DOL_RADIUS + outline, START_Y / 2 + DOL_RADIUS + outline);
    }
    else
    {
        Ellipse(hdc, WIN_WIDTH / 2 + DOL_SIZE * 2 - DOL_RADIUS - outline, START_Y / 2 - DOL_RADIUS - outline,
                     WIN_WIDTH / 2 + DOL_SIZE * 2 + DOL_RADIUS + outline, START_Y / 2 + DOL_RADIUS + outline);
    }

    SelectObject(hdc, GetStockObject(BLACK_BRUSH));
    Ellipse(hdc, WIN_WIDTH / 2 - DOL_SIZE * 2 - DOL_RADIUS, START_Y / 2 - DOL_RADIUS,
                 WIN_WIDTH / 2 - DOL_SIZE * 2 + DOL_RADIUS, START_Y / 2 + DOL_RADIUS);

    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
    Ellipse(hdc, WIN_WIDTH / 2 + DOL_SIZE * 2 - DOL_RADIUS, START_Y / 2 - DOL_RADIUS,
                 WIN_WIDTH / 2 + DOL_SIZE * 2 + DOL_RADIUS, START_Y / 2 + DOL_RADIUS);

    //바둑판에 놓인 돌 렌더링
    for (int y = 0; y < Y_COUNT; ++y)
    {
        for (int x = 0; x < X_COUNT; ++x)
        {
            if (g_omokBoard[y][x] == OMOKDOL::NONE)
                continue;

            if (g_omokBoard[y][x] == OMOKDOL::BLACK)
                SelectObject(hdc, GetStockObject(BLACK_BRUSH));
            else
                SelectObject(hdc, GetStockObject(WHITE_BRUSH));

            Ellipse(hdc, XPOS(x) - DOL_RADIUS, YPOS(y) - DOL_RADIUS,
                         XPOS(x) + DOL_RADIUS, YPOS(y) + DOL_RADIUS);
        }
    }

    EndPaint(hWnd, &ps);
}

void ONLButtonDown(HWND hWnd, int x, int y)
{
    // 바둑판 범위 안 에 있는지 
    if (x > (XPOS(0)-DOL_RADIUS) && y > (YPOS(0)-DOL_RADIUS)
        && x < (XPOS(X_COUNT - 1 + DOL_RADIUS))
        && y < (YPOS(Y_COUNT - 1 + DOL_RADIUS)))
    {
        int ux = (x - START_X + DOL_RADIUS) / DOL_SIZE;
        int uy = (y - START_Y + DOL_RADIUS) / DOL_SIZE;

        if (g_omokBoard[uy][ux] == OMOKDOL::NONE)
        {
            if (g_turn)
                g_omokBoard[uy][ux] = OMOKDOL::BLACK;
            else
                g_omokBoard[uy][ux] = OMOKDOL::WHITE;
            
            g_turn = !g_turn;
            g_count++;
            InvalidateRect(hWnd, nullptr, true);
        }
    }
}

//방향에 따른 오목 확인 
bool five_Check(OMOKDOL dol, int dy, int dx, int y, int x)
{
    for (int i = 0; i < 5; i++)
        if (g_omokBoard[y + (dy * i)][x + (dx * i)] != dol)
            return false;
    return true;
}

GAMESTATE IsGameOver()
{
    GAMESTATE result = GAMESTATE::READY;
    static const int four = 4;

    for (int y = 0; y < Y_COUNT; ++y)
    {
        for (int x = 0; x < X_COUNT; ++x)
        {
            if (g_omokBoard[y][x] == OMOKDOL::NONE)
                continue;

            //가로 체크
            if (x + four < X_COUNT && five_Check(OMOKDOL::BLACK, 0, 1, y, x))
                return GAMESTATE::BLACK_WIN;
            if (x + four < X_COUNT && five_Check(OMOKDOL::WHITE, 0, 1, y, x))
                return GAMESTATE::WHITE_WIN;
            
            //세로 체크
            if (y + four < Y_COUNT && five_Check(OMOKDOL::BLACK, 1, 0, y, x))
                return GAMESTATE::BLACK_WIN;
            if (y + four < Y_COUNT && five_Check(OMOKDOL::WHITE, 1, 0, y, x))
                return GAMESTATE::WHITE_WIN;

            //좌측하단 체크
            if (x - four >= 0 && y - four >= 0 && five_Check(OMOKDOL::BLACK, -1, -1, y, x))
                return GAMESTATE::BLACK_WIN;
            if (x - four >= 0 && y - four >= 0 && five_Check(OMOKDOL::WHITE, -1, -1, y, x))
                return GAMESTATE::WHITE_WIN;

            //우측하단 체크
            if (x + four < X_COUNT && y - four >= 0 && five_Check(OMOKDOL::BLACK, -1, 1, y, x))
                return GAMESTATE::BLACK_WIN;
            if (x + four < X_COUNT && y - four >= 0 && five_Check(OMOKDOL::WHITE, -1, 1, y, x))
                return GAMESTATE::WHITE_WIN;
        }
    }

    if (g_count == X_COUNT * Y_COUNT)
        result = GAMESTATE::TIE_GAME;
    return result;
}
