#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
using namespace std;
#pragma comment(lib, "winmm.lib")

int main()
{
	PlaySound(L"explosion.wav", NULL, SND_FILENAME | SND_ASYNC);

	for (int i = 0; i < 3; ++i)
	{
		cout << "\r" << 3 - i << "...";
		Sleep(1000);
	}
}