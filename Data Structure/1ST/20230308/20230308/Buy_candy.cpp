#include <iostream>

using namespace std;

int main()
{
	int thisMoney, price;

	cout << "���� ������ �ִ� �� : ";
	cin >> thisMoney;
	cout << "ĵ���� ���� : ";
	cin >> price;
	cout << "�ִ�� �� �� �ִ� ĵ���� ���� = " << thisMoney / price << "\n";
	cout << "ĵ�� ���� �� ���� �� = " << thisMoney % price << endl;
}