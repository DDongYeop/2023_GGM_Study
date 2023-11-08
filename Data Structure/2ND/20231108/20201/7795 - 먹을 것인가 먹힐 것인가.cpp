#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int loop, loop1, loop2, input, answer;
	cin >> loop;

	while (loop--)
	{
		cin >> loop1 >> loop2;
		vector<int> vec1, vec2;
		answer = 0;
		while (loop1--)
		{
			cin >> input;
			vec1.push_back(input);
		}

		while (loop2--)
		{
			cin >> input;
			vec2.push_back(input);
		}

		sort(vec1.begin(), vec1.end());
		sort(vec2.begin(), vec2.end());


		for (auto i : vec1)
			answer += lower_bound(vec2.begin(), vec2.end(), i) - vec2.begin();
		
		cout << answer << '\n';
	}
}
