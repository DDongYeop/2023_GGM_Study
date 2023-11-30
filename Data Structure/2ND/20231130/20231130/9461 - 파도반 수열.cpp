#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int t,n;
	vector<long long> vec(101);

	cin >> t;
	
	vec[1] = vec[2] = vec[3] = 1;
	for (int i = 4; i < 101; ++i)
		vec[i] = vec[i - 2] + vec[i - 3];

	while (t--)
	{
		cin >> n;
		cout << vec[n] << '\n';
	}
}
