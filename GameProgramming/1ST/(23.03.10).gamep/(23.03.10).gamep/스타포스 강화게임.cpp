#include <iostream>

using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	cout << "=================" << endl;
	cout << "��Ÿ���� ��ȭ ����" << endl;
	cout << "=================" << endl << endl;
	int iUpgrade = 0;
	float fPercent = 0.f;
	cout << "���� ����� ��ΰ���?" << endl;
	cin >> iUpgrade;
	switch (iUpgrade)
	{
	case 0:
	case 1:
	case 2:
		fPercent = 90;
		break;
	case 3:
	case 4:
	case 5:
		fPercent = 50;
		break;
	case 6:
	case 7:
	case 8:
	case 9:
		fPercent = 10;
		break;
	default:
		fPercent = 1;
		break;
	}
	cout << "���� ���� UPgrade : " << iUpgrade << "��" << endl;
	cout << "��ȭ Ȯ�� Percent : " << fPercent << "%" << endl;
	cout << "��ȭ�Ͻðڽ��ϱ�? ��:1 , �ƴϿ�: 0" << endl;
	int iInput;
	cin >> iInput;

	if (iInput == 0) //�������� ó��.
		return 0;

	if (fPercent > rand() % 101 + 1)
		cout << "��ȭ ����";
	else
		cout << "��ȭ ����";
}
