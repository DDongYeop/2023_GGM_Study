#include <iostream>
#include <Windows.h>
using namespace std;
// enum: ���� ���� (C++98) vs enum class: ���� �ִ� (C++ 11)
enum class AI_MODE
{
	EASY = 1,
	NORMAL
};

enum class LINE_NUMBER
{
	LN_H1, LN_H2, LN_H3, LN_H4, LN_H5,
	LN_V1, LN_V2, LN_V3, LN_V4, LN_V5,
	LN_LT, LN_RT
};

void Init(int* _pNumber)
{
	//�ʱ�ȭ: ����, 
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
	// for�� ������ 
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

	//�밢���� ���� üũ LT
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

AI_MODE SelectAiMode()
{
	cout << "===============" << endl;
	cout << " | ���� ���� | " << endl;
	cout << "===============" << endl;
	cout << "�������� 5�� �̻��� �Ǹ� ���ӿ��� �¸��մϴ�." << endl;
	cout << "1.EASY\n2.NORMAL\nAI��带 �����ϼ���. \n";
	int iAimode;
	cin >> iAimode;
	//����

	if (iAimode < static_cast<int>(AI_MODE::EASY) || iAimode > static_cast<int>(AI_MODE::NORMAL))
	{
		cout << "�߸� �Է��߽��ϴ�.\n";
		Sleep(500);
		system("cls");
		return SelectAiMode();
	}
	return static_cast<AI_MODE>(iAimode);
}

int SelectAiNumber(int *_pNumber, AI_MODE _eMode)
{
	int iNoneSelect[25] = {};
	int iNoneSelectCnt = 0;
	switch (_eMode)
	{
	case AI_MODE::EASY:
	{
		for (int i = 0; i < 25; ++i)
		{
			iNoneSelectCnt = 0;
			//���ڴ�
			if (_pNumber[i] != INT_MAX)
			{
				iNoneSelect[iNoneSelectCnt] = _pNumber[i];
				++iNoneSelectCnt;
			}
		}
		return iNoneSelect[rand() % iNoneSelectCnt];
	}
		break;
	case AI_MODE::NORMAL:
	{
		int iLine = 0;
		int iStarcnt = 0;
		int iSavecnt = 0;
		//������ üũ
		for (int i = 0; i < 5; ++i)
		{
			iStarcnt = 0;
			for (int j = 0; j < 5; ++j)
			{
				if (_pNumber[i * 5 + j] == INT_MAX)
					++iStarcnt;
			}
			//������ üũ �Ϸ� 
			if (iStarcnt < 5 && iStarcnt > iSavecnt)
			{
				iLine = i;
				iSavecnt = iStarcnt;
			}
		}
		//������ üũ
		for (int i = 0; i < 5; ++i)
		{
			iStarcnt = 0;
			for (int j = 0; j < 5; ++j)
			{
				if (_pNumber[j * 5 + i] == INT_MAX)
					++iStarcnt;
			}
			//������ üũ �Ϸ� 
			if (iStarcnt < 5 && iStarcnt > iSavecnt)
			{
				iLine = i+5;
				iSavecnt = iStarcnt;
			}
		}
		//LT�밢��
		iStarcnt = 0;
		for (int i = 0; i < 25; i += 6)
		{
			if (_pNumber[i] == INT_MAX)
				++iStarcnt;
		}
		if (iStarcnt < 5 && iStarcnt > iSavecnt)
		{
			iLine = (int)LINE_NUMBER::LN_LT;
			iSavecnt = iStarcnt;
		}
		//RT�밢��
		iStarcnt = 0;
		for (int i = 4; i < 25; i += 4)
		{
			if (_pNumber[i] == INT_MAX)
				++iStarcnt;
		}
		if (iStarcnt < 5 && iStarcnt > iSavecnt)
		{
			iLine = (int)LINE_NUMBER::LN_RT;
			iSavecnt = iStarcnt;
		}

		//���� ���� iLine�� �˰� �Ǿ���
		if (iLine <= (int)LINE_NUMBER::LN_H5)
		{
			for (int i = 0; i < 5; ++i)
			{
				if (_pNumber[iLine*5+i] != INT_MAX)
				{
					return _pNumber[iLine * 5 + i];
				}
			}
		}
		if (iLine <= (int)LINE_NUMBER::LN_V5)
		{
			for (int i = 0; i < 5; ++i)
			{
				if (_pNumber[i*5 + (iLine - 5)] != INT_MAX)
				{
					return _pNumber[i * 5 + (iLine - 5)];
				}
			}
		}
		//LT
		else if (iLine == (int)LINE_NUMBER::LN_RT)
		{
			for (int i = 0; i < 25; i += 6)
				if (_pNumber[i] != INT_MAX)
					return _pNumber[i];
		}
		else if (iLine == (int)LINE_NUMBER::LN_LT)
		{
			for (int i = 4; i < 20; i += 4)
				if (_pNumber[i] != INT_MAX)
					return _pNumber[i];
		}
	}
		break;
	}
	return -1;
}

int main()
{
	srand((unsigned int)time(NULL));
	int iNumber[25] = {};
	int iAiNumber[25] = {};
	int iBingo = 0, iAiBingo = 0;
	int iInput;
	Init(iNumber);
	Init(iAiNumber);
	AI_MODE eMode = SelectAiMode();
	while (true)
	{
		system("cls");
		cout << "======================== Player ========================\n";
		RenderNumber(iNumber, iBingo);
		cout << "========================   AI   ========================\n";
		switch (eMode)
		{
		case AI_MODE::EASY:
			cout << "AIMODE: EASY\n";
			break;
		case AI_MODE::NORMAL:
			cout << "AIMODE: NORMAL\n";
			break;
		}
		RenderNumber(iAiNumber, iAiBingo);
		if (iBingo >= 5)
		{
			cout << "���ӿ��� �¸� �Ͽ����ϴ�. " << endl;
			break;
		}
		else if (iAiBingo >= 5)
		{
			cout << "AI�� ���ӿ��� �¸� �Ͽ����ϴ�. " << endl;
			break;
		}
		cout << "���ڸ� �Է��ϼ���. (0: ����)  ";
		cin >> iInput;
		//�������� �� ����ó��
		if (iInput == 0)
		{
			cout << "������ �����մϴ�. " << endl;
			break;
		}
		else if (iInput < 1 || iInput > 25)
		{
			cout << "�߸� �Է��Ͽ����ϴ�. " << endl;
			continue;
		}
		// �Էµ� ���ڸ� ���� �ٲٱ� 
		BingoCheck(iNumber, iInput);
		BingoCheck(iAiNumber, iInput);

		//AI turn
		iInput = SelectAiNumber(iAiNumber, eMode);
		cout << "AI�� ������ ���ڴ� " << iInput << "�Դϴ�. " << endl;
		Sleep(1000);

		// �Էµ� ���ڸ� ���� �ٲٱ� 
		BingoCheck(iNumber, iInput);
		BingoCheck(iAiNumber, iInput);

		// �� üũ�ؼ� ���̺��� �ø��� 
		iBingo = BingoCount(iNumber);
		iBingo = BingoCount(iAiNumber);
	}
}
