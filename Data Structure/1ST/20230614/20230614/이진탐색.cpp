#include <iostream>
#include <vector>

using namespace std;

void BinarySearch(vector<int>& age);

int main()
{
	vector<int> age;
	int min, max;
	cout << "나이의 최소값, 최대값 입력 : ";
	cin >> min >> max;
	for (int i = min; i < max; ++i)
		age.push_back(i);
	cout << "나이가 맞다면 YES, 더 많다면 UP, 더 적다면 DOWN을 입력.\n";
	BinarySearch(age);
}

void BinarySearch(vector<int>& age)
{
	int left = age[0];
	int right = age[age.size() - 1];
	int mid = (right - left) / 2 + left;
	string str;

	while (true)
	{
		cout << age[mid] << "살 입니까? : ";
		cin >> str;

		switch (str[0])
		{
		case 'U':
			left = mid;
			mid = (right - left) / 2 + left;
			break;
		case 'D':
			right = mid;
			mid = (right - left) / 2 + left;
			break;
		case 'Y':
			cout << "WOW~!!";
			return;
			break;
		}
	}
}
