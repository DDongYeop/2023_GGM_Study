#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int loop, money, input, coin = 0;
	vector<int> vec;
	cin >> loop >> money;

	while (loop--)
	{
		cin >> input;
		vec.push_back(input);
	}

	while (money)
	{
		for (int i = 0; i < vec.size(); ++i)
		{
			if (money < vec[i])
			{
				money -= vec[i - 1];
				++coin;
				break;
			}
			else if (i == vec.size() - 1)
			{
				money -= vec[i];
				++coin;
				break;
			}
		}
	}

	cout << coin;
}