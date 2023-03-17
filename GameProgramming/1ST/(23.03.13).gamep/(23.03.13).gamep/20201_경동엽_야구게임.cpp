#include <iostream>

using namespace std;

void Shuffle(int iNumber[]);
int BaseBallGame(int iNumber[], int iInput[]);

int main()
{
	int iNumber[9] = {};
	for (int i = 0; i < 9; i++)
		iNumber[i] = i + 1;
	
	srand((unsigned int)time(NULL));
	cout << "* * *" << endl;

	int iInput[3];
	int iGamecnt = 0, iPlayerNum= 0;
	while (true)
	{
		cout << iGamecnt << "회" << endl;
		if (iPlayerNum % 2 == 0)
			cout << "Player1 : ";
		else
			cout << "Player2 : ";
		cout << "1 ~ 9 사이의 숫자 중 숫자 3개를 입력하세요(0: 종료): ";
		cin >> iInput[0] >> iInput[1] >> iInput[2];
		
		//종료조건. 
		if (iInput[0] == 0 || iInput[1] == 0 || iInput[2] == 0)
			break;
		// 예외처리. 0, 10, 1000, 1 2 2
		else if (iInput[0] <= 0 || iInput[0] > 9 ||
				 iInput[1] <= 0 || iInput[1] > 9 ||
				 iInput[2] <= 0 || iInput[2] > 9)
		{
			cout << "잘못된 숫자를 입력했어요. 1~9사이 숫자만 입력해주세요. " << endl;
			continue;
		}
		else if (iInput[0] == iInput[1] || iInput[1] == iInput[2] || iInput[2] == iInput[0])
		{
			cout << "동일한 숫자를 입력했어요. 중복된 숫자는 금지입니다. " << endl;
			continue;
		}
		BaseBallGame(iNumber, iInput);
		if (BaseBallGame(iNumber, iInput) == 1)
			break;
		

		iGamecnt++;
		iPlayerNum++;
	}
}

void Shuffle(int iNumber[]) //Shuffle 알고리즘
{
	int idx1, idx2, temp;

	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 9;
		idx2 = rand() % 9;
		temp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = temp;
	}
}

int BaseBallGame(int iNumber[], int iInput[])
{
	int iStrike = 0, iBall = 0;

	iStrike = iBall = 0;
	// strike, ball 체크 iNumber, iInput
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (iNumber[i] == iInput[j])
			{
				if (i == j)
					iStrike++;
				else
					iBall++;
			}
		}
	}

	if (iStrike == 3)
	{
		system("cls");
		cout << "숫자를 모두 맞췄어요. " << endl;
		return 1;
	}
	else if (iStrike == 0 && iBall == 0)
		cout << "Out" << endl;
	else
		cout << iStrike << "strike  " << iBall << "ball" << endl;
}



// Shuffle 알고리즘 사용
// 함수로 나누고, 2인용으로 바꿔라 