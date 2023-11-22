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
	cout << lower_bound(num) << '\n'; // 7������ 6, 6 ������ 6
	cout << upper_bound(num) << '\n'; // 7������ 7, 6������ 6
}

int lower_bound(int key)
{
	int left = 0, right = v.size(), mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (v[mid] >= key)		//Ư�� ���� (key�� �̻�) ����
			right = mid -1;	//Ư�� ������ �����ϴ� ���� �� ã��
		else
			left = mid + 1;		//�� ū �� �߿��� �����ϴ� �� ã���� ����
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
