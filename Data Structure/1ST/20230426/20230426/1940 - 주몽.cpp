#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n = 0, m;
	int x, cnt = 0;
	cin >> n >> m;
	vector<int> vec;

	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		vec.push_back(x);
	}

	for (int i = 0; i < vec.size(); ++i)
	{
		for (int j = i; j < vec.size(); ++j)
		{
			if (i == j)
				continue;

			if (m == (vec[i] + vec[j]))
				++cnt;
		}
	}

	cout << cnt;
}
