#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

bool Compare(tuple<int, int, float> t1, tuple<int, int, float> t2);

int main()
{
	int input1, input2, currentWeight = 8, currentValue = 0;
	vector<tuple<int, int, float>> vec;

	for (int i = 0; i < 5; ++i)
	{
		cin >> input1 >> input2;
		vec.push_back(make_tuple(input1, input2, (float)input2 / (float)input1));
	}
	sort(vec.begin(), vec.end(), Compare);

	for (int i = 0; i < vec.size(); ++i)
	{
		if (currentWeight < get<1>(vec[i]))
		{
			currentValue += get<2>(vec[i]) * currentValue;
			break;
		}
		else
		{
			currentValue += get<2>(vec[i]) * get<1>(vec[i]);
			currentWeight -= get<1>(vec[i]);
		}

		if (currentWeight <= 0)
			break;
	}

	cout << currentValue;
}

bool Compare(tuple<int, int, float> t1, tuple<int, int, float> t2)
{
	return get<2>(t1) > get<2>(t1);
}
