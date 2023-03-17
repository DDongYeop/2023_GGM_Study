#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

enum Level { EASY = 1, NORMAL=2, HARD=3};

void NumberGame(int iNumber[], Level level);

int main()
{
	srand((unsigned int)time(NULL));
	cout << "====================================\n";
	cout << "숫자 기억 게임입니다. 모드를 선택하세요\n";
	cout << "  EASY : 1   NORMAL : 2    HARD : 3  \n";
	cout << "====================================\n";
	int index;
	cin >> index;
	system("cls");
	switch (index) // {}사용하면 선언 할 수 있다 
	{
	case EASY:
	{
		int iNumber[EASY * 5];
		NumberGame(iNumber, EASY);
	} break;
	case NORMAL:
	{
		int iNumber[NORMAL * 5];
		NumberGame(iNumber, NORMAL);
	} break;
	case HARD:
	{
		int iNumber[HARD * 5];
		NumberGame(iNumber, HARD);
	} break;
	}
}


void NumberGame(int iNumber[], Level level)
{
	int iInput;
	for (int i = 0; i < level * 5; i++) //뽑아냄
		iNumber[i] = rand() % 101;

	for (int i = 0; i < level * 5; i++)
	{
		cout << iNumber[i] << " ";
		Sleep(1000);
	}
	system("cls");
	cout << level << "모드 입니다. 방금 본 숫자를 입력하세요. : " << endl;
	for (int i = 0; i < level * 5; i++)
	{
		cin >> iInput;
		if (iNumber[i] != iInput)
		{
			cout << "떙 틀렸습니다. ";
			return;
		}
	}

	cout << "정답입니다 !";
}


//이것도 함수로 바꿔오기