#include <iostream>

using namespace std;

int main()
{
	cout << "=================" << endl;
	cout << "��Ÿ���� ��ȭ ����" << endl;
	cout << "=================" << endl << endl;
	int iUpgrade = 0;
	float fPercent = 0.f;
	cout << "���� ����� ��ΰ���?" << endl;
	cin >> iUpgrade;
	cout << "���� ���� UPgrade : " << iUpgrade << "��" << endl;
	cout << "��ȭ Ȯ�� Percent : " << fPercent << "%" << endl;
	cout << "��ȭ�Ͻðڽ��ϱ�? ��:1 , �ƴϿ�: 0" << endl;
	int iInput;
	cin >> iInput;

	if (iInput == 0) //�������� ó��.
		return 0;
}
