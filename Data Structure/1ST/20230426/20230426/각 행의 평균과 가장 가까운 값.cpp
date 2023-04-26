#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	float sum = 0;
	int array[9], num;
	int resultArray[9][2];
	
	for (int i = 0; i < 9; ++i)
	{
		resultArray[i][1] = 99;
		sum = 0;
		for (int j = 0; j < 9; ++j)
		{
			cin >> array[j];
			sum += array[j];
		}
		resultArray[i][0] = floor((sum /= 9) + 0.5f);
		for (int j = 0; j < 9; ++j)
		{
			sum = resultArray[i][0] - array[j];
			if (sum < 0)
				sum *= -1;
			if (resultArray[i][1] > sum)
			{
				resultArray[i][1] = sum;
				num = j;
			}
		}
		resultArray[i][1] = array[num];
	}

	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 2; ++j)
			cout << resultArray[i][j] << ' ';
		cout << '\n';
	}
}

// 입력 예시
// 3 23 85 34 17 74 25 52 65
// 10 7 39 42 88 52 14 72 63
// 87 42 18 78 53 45 18 84 53
// 34 28 64 85 12 16 75 36 55
// 21 77 45 35 28 75 90 76 1
// 25 87 65 15 28 11 37 28 74
// 65 27 75 41 7 89 78 64 39
// 47 47 70 45 23 65 3 41 44
// 87 13 82 38 50 12 48 29 80
