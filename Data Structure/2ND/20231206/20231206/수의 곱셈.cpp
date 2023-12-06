#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(int idx1, int idx2);

int main()
{
		vector<int> vec;
	int input, answer = 1;

	for (int i = 0; i < 3; ++i)
	{
		cin >> input;
		vec.push_back(input);
	}

	sort(vec.begin(), vec.end(), compare);

	if (vec[0] % 2 == 0)
	{
		for (int i : vec)
		{
			if (i % 2 == 0)
				break;
			answer *= i;
		}
	}
	else
	{
		for (int i : vec)
			answer *= i;
	}

	cout << answer;
}

bool compare(int idx1, int idx2)
{
	if (idx1 % 2 == 0 && idx2 % 2 == 0)
		return idx1 > idx2 ? idx1 : idx2;
	return idx1 % 2 == 0 ? idx1 : idx2 % 2 == 0 ? idx2 : idx1 > idx2 ? true : false;
}
