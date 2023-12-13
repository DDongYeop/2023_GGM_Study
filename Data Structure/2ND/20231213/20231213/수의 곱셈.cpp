#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int answer = 1, input;
	vector<int> evenVec, oddVec;

	for (int i = 0; i < 3; ++i)
	{
		cin >> input;
		if (input % 2 == 0)
			evenVec.push_back(input);
		else
			oddVec.push_back(input);
	}

	if (oddVec.size() != 0)
	{
		for (auto i : oddVec)
			answer *= i;
	}
	else
	{
		for (auto i : evenVec)
		{
			if (i == 0)
				continue;
			answer *= i;
		}
	}

	cout << answer;
}
