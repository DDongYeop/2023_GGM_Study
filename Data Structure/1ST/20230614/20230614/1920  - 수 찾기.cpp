#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, m, input, num;
	vector<int> v1;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> input;
		v1.push_back(input);
	}
	sort(v1.begin(), v1.end());

	cin >> m;
	for (int i = 0; i < m; ++i)
	{
		cin >> input;
		num = *lower_bound(v1.begin(), v1.end() - 1, input);
		if (num == input)
			cout << "1\n";
		else
			cout << "0\n";
	}
}
