#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n, k, input;
	vector<vector<int>> vec;

	cin >> n >> k;

	for (int i = 0; i < n / k; ++i)
	{
		vec.push_back(vector<int>());
		for (int j = 0; j < k; ++j)
		{
			cin >> input;
			vec[i].push_back(input);
		}
	}

	for (auto v : vec)
	{
		for (auto i : v)
			cout << i << ' ';
		cout << '\n';
	}
}
