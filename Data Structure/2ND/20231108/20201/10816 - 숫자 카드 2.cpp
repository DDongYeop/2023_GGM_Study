#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int loop, input;
	vector<int> vec;

	cin >> loop;
	while (loop--)
	{
		cin >> input;
		vec.push_back(input);
	}

	sort(vec.begin(), vec.end());

	cin >> loop;
	while (loop--)
	{
		cin >> input;
		cout << upper_bound(vec.begin(), vec.end(), input) - lower_bound(vec.begin(), vec.end(), input) << ' ';
	}
}
