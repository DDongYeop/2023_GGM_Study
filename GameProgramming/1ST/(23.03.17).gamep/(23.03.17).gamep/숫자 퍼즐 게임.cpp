#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

void Init(int* _pNumber);
void RenderNumber(int* _pNumber);
char Update(int* _pNumber);
void PuzzleCheck(int* _pNumber);
// ������, �ּ�����, ��������

int main()
{
	// 1���� �迭
	int iNumber[25] = {};
	Init(iNumber);
	while (true)
	{
		system("cls");
		RenderNumber(iNumber);
		PuzzleCheck(iNumber);
		char cChk = Update(iNumber);
		if (cChk == 'q' || cChk == 'Q')
			break;
	}
}

void Init(int *_pNumber)
{
	//�ʱ�ȭ: ����, 
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 24; i++)
		_pNumber[i] = i + 1;
	_pNumber[24] = INT_MAX;

	int iTemp, idx1, idx2;
	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 24; // 1 ~ 24
		idx2 = rand() % 24; // 1 ~ 24

		iTemp = _pNumber[idx1];
		_pNumber[idx1] = _pNumber[idx2];
		_pNumber[idx2] = iTemp;
	}
}

void RenderNumber(int* _pNumber)
{
	cout << "===================" << endl;
	cout << " | ���� ���� ���� | " << endl;
	cout << "*�� �������� 1~24���� ������ ���纸����. " << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (_pNumber[i * 5 + j] == INT_MAX)
				cout << "*" << "\t";
			else
				cout << _pNumber[i * 5 + j] << "\t";
		}
		cout << endl;
	}
}

char Update(int* _pNumber)
{
	cout << "w:��, s:�Ʒ�, a: ����, d:������, q:����" << endl;
	static int iStarindex = 24;
	char cInput = _getch();
	switch (cInput)
	{
	case 'w':
	case 'W':
	{
		if (iStarindex > 4)
		{
			_pNumber[iStarindex] = _pNumber[iStarindex - 5];
			_pNumber[iStarindex - 5] = INT_MAX;
			iStarindex -= 5;
		}
	}
		break;
	case 's': 
	case 'S':
	{
		if (iStarindex < 20)
		{
			_pNumber[iStarindex] = _pNumber[iStarindex + 5];
			_pNumber[iStarindex + 5] = INT_MAX;
			iStarindex += 5;
		}
	}
		break;
	case 'a': 
	case 'A':
	{
		if (iStarindex % 5 != 0)
		{
			_pNumber[iStarindex] = _pNumber[iStarindex - 1];
			_pNumber[iStarindex - 1] = INT_MAX;
			iStarindex -= 1;
		}
	}
		break;
	case 'd': 
	case 'D':
	{
		if (iStarindex % 5 != 4)
		{
			_pNumber[iStarindex] = _pNumber[iStarindex + 1];
			_pNumber[iStarindex + 1] = INT_MAX;
			iStarindex += 1;
		}
	}
		break;
	// �����ض� 
  /*case 'q':
	case 'Q':
	{
		exit(0);
	}
		break;*/
	default:
		break;
	}
	return cInput;
}

void PuzzleCheck(int* _pNumber)
{
	for (int i = 0; i < 24; i++)
		if (_pNumber[i] != i + 1)
			return;

	cout << "�����մϴ�. Ŭ�����ϼ̽��ϴ�. " << endl;
}
