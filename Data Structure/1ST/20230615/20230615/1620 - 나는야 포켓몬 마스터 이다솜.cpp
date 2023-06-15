#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int x, y;
	string input;
	map<int, string> m1;
	map<string, int> m2;
	cin >> x >> y;
	
	for (int i = 0; i < x; ++i)
	{
		cin >> input;
		m1.insert(make_pair(i + 1, input));
		m2.insert(make_pair(input, i + 1));
	}

	for (int i = 0; i < y; ++i)
	{
		cin >> input;

		if ('0' <= input[0] && input[0] <= '9')
			cout << m1[stoi(input)] << '\n';
		else
			cout << m2[input] << '\n';

	}
}
