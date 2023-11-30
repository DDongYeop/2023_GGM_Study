#include <iostream>
#include <vector>

using namespace std;

int Fibo(int n);

vector<int> vec;

int main()
{
	vec.resize(100001, 0);

	int n;
	cin >> n;
	vec[1] = vec[2] = 1;
	for (int i = 3; i <= n; ++i)
	{
		if (vec[n] == 0)
			vec[i] = vec[i - 1] + vec[i - 2];
	}

	cout << vec[n];
}
