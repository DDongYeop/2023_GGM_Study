#include <iostream>

using namespace std;

int main()
{
	int arr[100];
	arr[0] = arr[1] = 1;

	for (int i = 2; i < 100; ++i)
		arr[i] = arr[i - 1] + arr[i - 2];
}
