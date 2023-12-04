#include <iostream>
#include <vector>

using namespace std;

int dp[1000001] = { 0 };
vector<int> vec;

int main()
{
	int n, k, input;
	cin >> n >> k;

	while (n--)
	{
		cin >> input;
		vec.push_back(input);
	}

	for (int i = 2; i <= k; ++i)
	{
	}

	cout << dp[n];
}
