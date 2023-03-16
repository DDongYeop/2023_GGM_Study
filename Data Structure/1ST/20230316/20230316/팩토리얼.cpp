#include <iostream>

using namespace std;

int Pack(int index);

int main()
{
	int index;
	cout << "팩토리얼 값을 구하고 싶은 숫자를 입력하시오 : ";
	cin >> index;
	cout << Pack(index);
}

int Pack(int index)
{
	if (index == 1)
		return 1;
	return index * Pack(index - 1);
}