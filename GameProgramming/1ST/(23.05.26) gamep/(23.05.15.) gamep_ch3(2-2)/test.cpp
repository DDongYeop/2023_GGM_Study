///*
//1. console 함수 하나 추가
//2. mci
//3. 파일입출력
//*/
//
//#include<iostream>
//#include<Windows.h>
//using namespace std;
void fontsize(UINT _weight, UINT _sizex, UINT _sizey)
{
	static CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof(font);
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hout, false, &font);
	font.FontWeight = _weight;
	font.dwFontSize.X = _sizex;
	font.dwFontSize.Y = _sizey;
	SetCurrentConsoleFontEx(hout, false, &font);
}
//int main()
//{
//	fontsize(FW_THIN, 100, 100);
//	cout << "테스트";
//}