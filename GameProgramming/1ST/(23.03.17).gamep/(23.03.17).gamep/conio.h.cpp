#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

int main()
{
	// getch(), kbhit() //둘다 언더바 붙여야한다 
	while (true)
	{
		if (_kbhit())
		{
			char ch = _getch();
			cout << "입력된 것은 " << ch << "입니다" << endl;
			cout << "int로 형변환하면 " << (int)ch << "입니다. " << endl << endl;
		}

		/*switch (ch)
		{
		case 'a':
		case 'A':
			break;
		default:
			break;
		}*/ //switch case문을 사용할때 a와 A따로 받아야한다 
	}
}
