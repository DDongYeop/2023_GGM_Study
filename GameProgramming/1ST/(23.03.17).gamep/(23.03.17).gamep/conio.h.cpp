#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

int main()
{
	// getch(), kbhit() //�Ѵ� ����� �ٿ����Ѵ� 
	while (true)
	{
		if (_kbhit())
		{
			char ch = _getch();
			cout << "�Էµ� ���� " << ch << "�Դϴ�" << endl;
			cout << "int�� ����ȯ�ϸ� " << (int)ch << "�Դϴ�. " << endl << endl;
		}

		/*switch (ch)
		{
		case 'a':
		case 'A':
			break;
		default:
			break;
		}*/ //switch case���� ����Ҷ� a�� A���� �޾ƾ��Ѵ� 
	}
}
