#include <iostream>
#include <Windows.h>
using namespace std;
// enum: 범위 없는 (C++98) vs enum class: 범위 있는 (C++ 11)
enum class AI_MODE
{
	EASY = 1,
	NORMAL
};

void Init(int* _pNumber)
{
	//초기화: 셔플, 
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 25; i++)
		_pNumber[i] = i + 1;

	int iTemp, idx1, idx2;
	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 25; // 1 ~ 25
		idx2 = rand() % 25; // 1 ~ 25

		iTemp = _pNumber[idx1];
		_pNumber[idx1] = _pNumber[idx2];
		_pNumber[idx2] = iTemp;
	}
}

void RenderNumber(int* _pNumber, int _iBingo)
{
	cout << "===============" << endl;
	cout << " | 빙고 게임 | " << endl;
	cout << "===============" << endl;
	cout << "빙고줄이 5줄 이상이 되면 게임에서 승리합니다." << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (_pNumber[i * 5 + j] == INT_MAX)
				cout << '*' << '\t';
			else
				cout << _pNumber[i * 5 + j] << "\t";
		}
		cout << endl;
	}
	cout << "bingo line : " << _iBingo << endl;
}

void BingoCheck(int* _pNumber, int iInput)
{
	// for문 돌리기 
	for (int i = 0; i < 25; i++)
	{
		if (_pNumber[i] == iInput)
		{
			_pNumber[i] = INT_MAX;
		}
	}
}

int BingoCount(int* _pNumber)
{
	int iBingo = 0;
	int iHorStar = 0, iVerStar = 0, iLTStar = 0, iRTStar = 0;
	for (int i = 0; i < 5; i++)
	{
		iHorStar = iVerStar = 0;
		for (int j = 0; j < 5; j++)
		{
			if (_pNumber[i*5+j] == INT_MAX)
				iHorStar++;
			if (_pNumber[j * 5 + i] == INT_MAX)
				iVerStar++;
		}
		if (iHorStar == 5)
			iBingo++;
		if (iVerStar == 5)
			iBingo++;
	}

	//대각선을 위한 체크 LT
	for (int i = 0; i < 25; i += 6)
		if (_pNumber[i] == INT_MAX)
			iLTStar++;
	if (iLTStar == 5)
		iBingo++;

	//RT
	for (int i = 4; i < 20; i += 4)
		if (_pNumber[i] == INT_MAX)
			iRTStar++;
	if (iRTStar == 5)
		iBingo++;

	return iBingo;
}

int main()
{
	int iNumber[25] = {};
	int iBingo = 0;
	int iInput;
	Init(iNumber);
	while (true)
	{
		system("cls");
		RenderNumber(iNumber, iBingo);
		if (iBingo >= 5)
		{
			cout << "게임에서 승리 하였습니다. " << endl;
			break;
		}
		cout << "숫자를 입력하세요. (0: 종료)  ";
		cin >> iInput;
		//종료조건 및 예외처리
		if (iInput == 0)
		{
			cout << "게임을 종료합니다. " << endl;
			break;
		}
		else if (iInput < 1 || iInput > 25)
		{
			cout << "잘못 입력하였습니다. " << endl;
			continue;
		}
		// 입력된 숫자를 별로 바꾸기 
		BingoCheck(iNumber, iInput);
		// 줄 체크해서 아이빙고를 늘린다 
		iBingo = BingoCount(iNumber);
	}
}
