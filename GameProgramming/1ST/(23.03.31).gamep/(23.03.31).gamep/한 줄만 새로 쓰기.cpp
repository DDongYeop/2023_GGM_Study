#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include "resource.h"
using namespace std;
#pragma comment(lib, "winmm.lib")

int main()
{
	// 1) ���� ��θ� ���ؼ� ���
	//PlaySound(L"explosion.wav", NULL, SND_FILENAME | SND_ASYNC);
	//PlaySound(L"explosion.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	//PlaySound(TEXT("explosion.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

	// 2) ���ҽ� ���ε� 
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE);

	for (int i = 0; i < 3; ++i)
	{
		cout << "\r" << 3 - i << "...";
		Sleep(1000);
	}
}