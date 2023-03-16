#include <iostream>

using namespace std;

int main()
{
	char array[3][3] {{' '}};
	int x, y;

	for (int k = 0; k < 9; k++)
	{
		cout << "(x, y) ÁÂÇ¥: ";
		cin >> x >> y;
		if (k % 2 == 0)
			array[x][y] = 'O';
		else
			array[x][y] = 'X';
		for (int i = 0; i < 3; i++) {
			cout << "---|---|---" << endl;
			cout << ' ' << array[i][0] << " | " << array[i][1] << "  |  " << array[i][2] << endl;
		}
		cout << "---|---|---" << endl;
	}
}