#include <iostream>
#include <map>

using namespace std;

int main()
{
	int input;
	string input2;
	map<string, int> m;

	cin >> input;

	for (int i = 0; i < input; ++i)
	{
		cin >> input2;

		++m[input2];
	}

	input = 0;

	for (auto num : m)
	{
		if (input < num.second)
		{
			input = num.second;
			input2 = num.first;
		}
	}

	cout << input2;
}
