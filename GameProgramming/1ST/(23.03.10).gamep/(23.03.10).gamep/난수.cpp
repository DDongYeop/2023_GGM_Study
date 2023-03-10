#include <iostream>
//#include <time.h>

using namespace std;

int main()
{
	int iNansu;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		iNansu = rand() % 10;
		cout << iNansu << endl;
	}
}