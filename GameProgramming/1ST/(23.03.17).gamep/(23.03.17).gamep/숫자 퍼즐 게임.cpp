#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

void Init(int* _pNumber);

int main()
{
	// 1차원 배열
	int iNumber[25] = {};
	Init(iNumber);
}

void Init(int *_pNumber)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 24; i++)
		_pNumber[i] = i + 1;
	_pNumber[24] = INT_MAX;
}
