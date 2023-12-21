#include <iostream>

using namespace std;

int main()
{
	int answer = 0;
	int currentNum = -1;
	string str;
	cin >> str;

	for (auto c : str)
	{
		if (48 <= c && c <= 57)
		{
			if (currentNum == -1)
				currentNum = c - 48;
			else
			{
				currentNum *= 10;
				currentNum += c - 48;
			}
		}
		else
		{
			if (currentNum == -1)
				continue;
			else
			{
				answer += currentNum;
				currentNum = -1;
			}
		}
	}

	cout << answer;
}
