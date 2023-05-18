#include <iostream>
#include <list>
using namespace std;

void FindValue(list<int> li, int value);

int main()
{
	int n, m, v, input;
	cin >> n >> m >> v;
	list<int> li;

	for (int i = 0; i < n; ++i)
	{
		cin >> input;
		li.push_back(input);
	}

	for (int i = 0; i < m; ++i)
	{
		cin >> input;

		if (input - m >= 0)
		{
			input -= v;
			int j = 0;
			while (input != 0)
			{
				--input;
				if (j == m)
					j = m - v;
				else
					++j;
			}

			FindValue(li, j);
		}
		else
			FindValue(li, input);
	}
}

void FindValue(list<int> li, int value)
{
	for (int i = 0; i < value; ++i)
		li.pop_front();
	cout << li.front() << ' ' << value  << '\n';
}
