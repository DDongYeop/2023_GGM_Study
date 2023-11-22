#include <iostream>
#include <vector>

using namespace std;

vector<int> v = { 0, 1, 2, 3, 4, 5, 7, 8 };

int lower_bound(int key);
int upper_bound(int key);

int main()
{
	int num;
	cin >> num;
	cout << lower_bound(num) << '\n'; // 7넣으면 6, 6 넣으면 6
	cout << upper_bound(num) << '\n'; // 7넣으면 7, 6넣으면 6
}

int lower_bound(int key)
{
	int left = 0, right = v.size(), mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (v[mid] >= key)		//특정 조건 (key값 이상) 만족
			right = mid -1;	//특정 조건을 만족하는 작은 값 찾기
		else
			left = mid + 1;		//더 큰 값 중에서 만족하는 값 찾으러 가기
	}
	return left;
}

int upper_bound(int key)
{
	int left = 0, right = v.size(), mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (v[mid] > key)
			right = mid -1;
		else
			left = mid + 1;
	}
	return left;
}
