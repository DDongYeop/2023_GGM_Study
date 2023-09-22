// (23.09.19).winapi.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "(23.09.19).winapi.h"
#include "Core.h"
#include "pch.h"
#include "BaseWindow.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    BaseWindow game;
    game.Run(hInstance, lpCmdLine, nCmdShow);
}
