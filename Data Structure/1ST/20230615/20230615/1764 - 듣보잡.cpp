#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
	int x, y, num = 0;
	string input;
	unordered_map<string, int> um;
	cin >> x >> y;

	for (int i = 0; i < x; ++i)
	{
		cin >> input;
		++um[input];
	}
	for (int i = 0; i < y; ++i)
	{
		cin >> input;
		++um[input];
		if (um.find(input)->second == 2)
			++num;
	}

	cout << num << '\n';
	for (auto m : um)
	{
		if (m.second >= 2)
			cout << m.first << '\n';
	}
}
