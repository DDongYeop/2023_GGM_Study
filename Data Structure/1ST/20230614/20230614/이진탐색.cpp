#include <iostream>
#include <vector>

using namespace std;

void BinarySearch(vector<int>& age);

int main()
{
	vector<int> age;
	int min, max;
	cout << "������ �ּҰ�, �ִ밪 �Է� : ";
	cin >> min >> max;
	for (int i = min; i < max; ++i)
		age.push_back(i);
	cout << "���̰� �´ٸ� YES, �� ���ٸ� UP, �� ���ٸ� DOWN�� �Է�.\n";
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
		cout << age[mid] << "�� �Դϱ�? : ";
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
