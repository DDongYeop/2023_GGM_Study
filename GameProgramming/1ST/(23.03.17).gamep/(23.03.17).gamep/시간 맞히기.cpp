#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

int main()
{
	long long llStartTime = time(NULL);
	cout << "===================" << endl;
	cout << "| �ð� ������ ���� |" << endl;
	cout << "===================" << endl << endl;

	cout << "===============================================================" << endl;
	cout << "���� : �ð��� ��� �����Դϴ�." << endl;
	cout << "ó�� key�� ���߿� ���� key�� ������ �ð��� 10�ʷ� �������ҽ��ϴ�." << endl;
	cout << "===============================================================" << endl << endl;

	cout << "=================" << endl;
	cout << "�ƹ�Ű�� ��������." << endl;
	cout << "=================" << endl << endl;

	char ch = _getch();

	cout << "���� !!" << endl;
	while (true)
	{
		if (_kbhit())
		{
			cout << "��!!!" << endl << endl;
			break;
		}
	}

	if (time(NULL) - llStartTime == 10)
		cout << "����� �̰���ϴ�. ";
	else
		cout << "����� �����ϴ�. ";
}
