#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
	string str;
	unordered_map<char, int> um;

	cin >> str;
	for (auto c : str)
		um[c]++;

	cin >> str;
	for (auto c : str)
		um[c]--;

	for (auto p : um)
	{
		if (p.second != 0)
		{
			cout << 0;
			return 0;
		}
	}
	cout << 1;
}
