#include <iostream>
#include <time.h>

using namespace std;

int main()
{

	srand((unsigned int)time(NULL));
	int randomnum = rand() % 4; // 0 ~ 3
	cout << randomnum << endl;
}