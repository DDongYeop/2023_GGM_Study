#include <iostream>
#include <list>
using namespace std;

int main()
{
	int n, k = 0, index = 0;
	list<int> li;
	cin >> n >> k;

	for (int i = 1; i <= n; ++i)
		li.push_back(i);

	cout << '<';
	while (li.size() != 1)
	{
		++index;
		if (k == index)
		{
			cout << li.front() << ", ";
			li.pop_front();
			index = 0;
		}
		else
		{
			li.push_back(li.front());
			li.pop_front();
		}
	}
	cout << li.front() << '>';
}
