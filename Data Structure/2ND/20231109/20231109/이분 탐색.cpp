#include <iostream>
#include <vector>

using namespace std;

vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };

int lower_bounce(int n)
{
	int left = 0, right = v.size() - 1, mid = (left + right) / 2;
	while (left <= right)
	{
		if (v[mid] > n)
			right = mid - 1;
		else
			left = mid + 1;
		mid = (left + right) / 2;
	}
	return mid;
}

int upper_bounce(int n)
{
	int left = 0, right = v.size() - 1, mid = (left + right) / 2;

	while (left < right)
	{
		if (v[mid] <= n)
			left = mid + 1;
		else
			right = mid;
		mid = (left + right) / 2;
	}
	return mid;
}

int main()
{
	int num;
	cin >> num;
	//cout << lower_bounce(num);
	cout << upper_bounce(num);
}
