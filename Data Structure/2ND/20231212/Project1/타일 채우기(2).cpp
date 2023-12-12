#include <iostream>

using namespace std;

int main()
{
	int arr[1001];

	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 3;

	for (int i = 3; i < 1001; ++i)
		arr[i] = (arr[i - 2] * 2) + arr[i - 1];
}
