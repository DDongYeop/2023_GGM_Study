#include <iostream>

using namespace std;

int Pack(int index);

int main()
{
	int index;
	cout << "���丮�� ���� ���ϰ� ���� ���ڸ� �Է��Ͻÿ� : ";
	cin >> index;
	cout << Pack(index);
}

int Pack(int index)
{
	if (index == 1)
		return 1;
	return index * Pack(index - 1);
}