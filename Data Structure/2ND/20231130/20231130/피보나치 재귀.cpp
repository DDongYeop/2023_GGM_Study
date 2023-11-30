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
	cout << Fibo(n);
}

int Fibo(int n)
{
	if (vec[n] != 0)
		return vec[n];

	if (n == 1 || n == 2)
		return 1;
	
	vec[n] = Fibo(n - 1) + Fibo(n - 2);
	return vec[n];
}
