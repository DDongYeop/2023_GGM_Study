#include <iostream>

using namespace std;

int main()
{
	cout << "구구단 중에서 출력하고 싶은 단을 입력하시오 : ";
	int index; 
	cin >> index;
	cout << endl;

	cout << "for" << endl;
	for (int i = 1; i <= 9; i++)
		cout << index << " * " << i << " = " << i * index << endl;

	cout << endl;

	cout << "범위기반 for" << endl;
	int arr[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (int i: arr)
		cout << index << " * " << i << " = " << i * index << endl;

	cout << endl;

	cout << "while" << endl;
	int x = 1;
	while (x <= 9)
	{
		cout << index << " * " << x << " = " << x * index << endl;
		x++;
	}

	cout << endl;

	cout << "do while" << endl;
	int y = 1;
	do
	{
		cout << index << " * " << y << " = " << y * index << endl;
		y++;
	} while (y <= 9);
}