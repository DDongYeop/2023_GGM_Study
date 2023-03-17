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
		cout << iGamecnt << "ȸ" << endl;
		if (iPlayerNum % 2 == 0)
			cout << "Player1 : ";
		else
			cout << "Player2 : ";
		cout << "1 ~ 9 ������ ���� �� ���� 3���� �Է��ϼ���(0: ����): ";
		cin >> iInput[0] >> iInput[1] >> iInput[2];
		
		//��������. 
		if (iInput[0] == 0 || iInput[1] == 0 || iInput[2] == 0)
			break;
		// ����ó��. 0, 10, 1000, 1 2 2
		else if (iInput[0] <= 0 || iInput[0] > 9 ||
				 iInput[1] <= 0 || iInput[1] > 9 ||
				 iInput[2] <= 0 || iInput[2] > 9)
		{
			cout << "�߸��� ���ڸ� �Է��߾��. 1~9���� ���ڸ� �Է����ּ���. " << endl;
			continue;
		}
		else if (iInput[0] == iInput[1] || iInput[1] == iInput[2] || iInput[2] == iInput[0])
		{
			cout << "������ ���ڸ� �Է��߾��. �ߺ��� ���ڴ� �����Դϴ�. " << endl;
			continue;
		}
		BaseBallGame(iNumber, iInput);
		if (BaseBallGame(iNumber, iInput) == 1)
			break;
		

		iGamecnt++;
		iPlayerNum++;
	}
}

void Shuffle(int iNumber[]) //Shuffle �˰���
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
	// strike, ball üũ iNumber, iInput
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
		cout << "���ڸ� ��� ������. " << endl;
		return 1;
	}
	else if (iStrike == 0 && iBall == 0)
		cout << "Out" << endl;
	else
		cout << iStrike << "strike  " << iBall << "ball" << endl;
}



// Shuffle �˰��� ���
// �Լ��� ������, 2�ο����� �ٲ�� 