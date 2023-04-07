#pragma once
enum class COLOR
{
	BALCK, BLUE, GREEN, SKYBLUE, RED, VIOLET, YELLOW, LIGHT_GRAY, GRAY, LIGHT_BLUE, LIGHT_GREEN, MINT, LIGHT_RED, LIGHY_VIOLET, LIGHT_YELLOW, WHITE
};
void FullScreen();
void Gotoxy(int, int);
void GotoxyPlayer(int x, int y);
BOOL GotoxyTest(int, int);
void Cursorset(bool, DWORD);
void SetColor(int color, int bgcolor);
int GetColor();
int GetbgColor();