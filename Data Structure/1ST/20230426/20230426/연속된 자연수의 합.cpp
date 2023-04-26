#include <iostream>
#include <vector>
using namespace std;

int FindValue(int i);

int num = 0, sum = 0;
int jIndex = 1;
vector<int> vec;

int main()
{
	cin >> num;

	for (int i = 1; i < num; ++i)
	{
		FindValue(i);
	}

	for (int i = 0; i < vec.size(); i += 2)
	{
		int index = vec[i];
		cout << vec[i];
		do
		{
			cout << " + ";
			++index;
			cout << index;
		} while (index != vec[i+1]);
		cout << " = " << num << '\n';
	}
	cout << vec.size() * 0.5f;
}

int FindValue(int i)
{
	sum = 0;
	for (int j = jIndex; j < num; ++j)
	{
		sum += j;
		if (num == sum)
		{
			vec.push_back(i + (vec.size() * 0.5f));
			vec.push_back(j);
			++jIndex;
			FindValue(i);
			return 0;
		}
		else if (num < sum)
		{
			++jIndex;
			return 0;
		}
	}
	return 0;
}
