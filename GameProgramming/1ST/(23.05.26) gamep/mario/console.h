#pragma once
#include<Windows.h>
enum class COLOR
{
	BLACK, BLUE, GREEN, SKYBLUE, RED,
	VIOLET, YELLOW, LIGHT_GRAY, GRAY,LIGHT_BLUE,
	LIGHT_GREEN, MINT, LIGHT_RED, LIGTH_VIOLET,
	LIGHT_YELLOW, WHITE
};
void FullScreen();
void Gotoxy(int, int);
void Gotoxyplayer(int, int);
BOOL Gotoxytest(int, int);
void Cursorset(bool, DWORD);
void SetColor(int color, int bgcolor);
int GetColor();
int GetbgColor();
void fontsize(UINT _weight, UINT _sizex, UINT _sizey);