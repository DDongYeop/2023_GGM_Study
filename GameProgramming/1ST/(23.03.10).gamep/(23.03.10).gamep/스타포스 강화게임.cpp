#include <iostream>

using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	cout << "=================" << endl;
	cout << "��Ÿ���� ��ȭ ����" << endl;
	cout << "=================" << endl << endl;
	int iUpgrade = 0;
	float fPercent = rand() % 10001 * 0.01f;
	cout << "���� ����� ��ΰ���?" << endl;
	cin >> iUpgrade;
	cout << "���� ���� UPgrade : " << iUpgrade << "��" << endl;
	cout << "��ȭ Ȯ�� Percent : " << fPercent << "%" << endl;
	cout << "��ȭ�Ͻðڽ��ϱ�? ��:1 , �ƴϿ�: 0" << endl;
	int iInput;
	cin >> iInput;

	if (iInput == 0) //�������� ó��.
		return 0;

	if (iUpgrade >= 0 && iUpgrade <= 2)
	{
		if (fPercent <= 90)
			cout << "��ȭ ����" << endl;
		else
			cout << "��ȭ ����" << endl;
	}
}
