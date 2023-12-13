#include <iostream>

using namespace std;

int main()
{
	int answer[21];

	answer[0] = 0; answer[1] = 1; answer[2] = 2; answer[3] = 3; answer[4] = 1; answer[5] = 1;

	for (int i = 6; i <= 20; ++i)
	{
		int idx1 = answer[i - 1] + 1;
		int idx2 = answer[i - 4] + 1;
		int idx3 = answer[i - 5] + 1;
		answer[i] = idx1 < idx2 ? idx1 < idx3 ? idx1 : idx3 : idx2 < idx3 ? idx2 : idx3;
	}

	int a = 1;
}
