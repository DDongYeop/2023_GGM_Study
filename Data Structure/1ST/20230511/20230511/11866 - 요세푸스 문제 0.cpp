#include <iostream>
#include <queue>
using namespace std;

int main()
{
	int n, k, num = 1;
	queue<int> que;
	cin >> n >> k;

	for (int i = 1; i <= n; ++i)
		que.push(i);

	cout << '<';
	while (que.size() != 0)
	{
		if (num == k)
		{
			cout << que.front();
			que.pop();
			if (que.size() != 0)
				cout << ", ";
			num = 1;
		}
		else
		{
			que.push(que.front());
			que.pop();
			++num;
		}
	}
	cout << '>';
}