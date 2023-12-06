#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int n, k, input, cnt = 0;
	vector<int> vec;
	cin >> n >> k;

	while(n--)
	{
		cin >> input;
		vec.push_back(input);
	}

	sort(vec.begin(), vec.end());
}
