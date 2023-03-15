#include <iostream>

using namespace std;

void Tic(int *array[3][4], char ch);

int main()
{
	int *array[3][4] = { {false} };

	while (true)
	{
		Tic(array, 'O');
		Tic(array, 'X');
	}
}

void Tic(int* array[3][4], char ch)
{
	int x, y;
	cout << "(x, y) ÁÂÇ¥ : ";
	cin >> x >> y;
	
	cout << "---|---|---";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (array[i][j])
				cout << ' ' << 'O' << ' ';
			else
				cout << "   ";
			if (j < 2)
				cout << '|';
		}
	}

}