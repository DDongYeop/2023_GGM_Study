#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

bool compare(tuple<int, int, int> t1, tuple<int, int, int> t2);

int main()
{
	int n, b, input1, input2, i;
	vector<tuple<int, int, int>> vec;
	bool isCoupon = false;
	cin >> n >> b;

	for (int i = 0; i < n; ++i)
	{
		cin >> input1 >> input2;
		vec.push_back(make_tuple(input1 + input2, input1, input2));
	}

	sort(vec.begin(), vec.end(), compare);

	for (i = 0; i < n; ++i)
	{
		if (b - get<0>(vec[i]) >= 0)
			b -= get<0>(vec[i]);
		else
		{
			if (isCoupon)
				break;

			isCoupon = true;
			if (get<1>(vec[i - 1]) > get<1>(vec[i]))
			{
				b += get<1>(vec[i - 1]) * 0.5f;
				--i;
			}
			else if (b - (get<0>(vec[i]) - get<1>(vec[i]) * 0.5f) >= 0)
				b -= (get<0>(vec[i]) - get<1>(vec[i]) * 0.5f);
			else
				break;
		}
	}

	cout << i;
}

bool compare(tuple<int, int, int> t1, tuple<int, int, int> t2)
{
	if (get<0>(t1) == get<0>(t2))
		return get<1>(t1) > get<1>(t2) ? true : false;

	return get<0>(t1) < get<0>(t2) ? true : false;
}
