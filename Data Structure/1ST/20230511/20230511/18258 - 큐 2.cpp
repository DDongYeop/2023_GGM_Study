#include <iostream>
#include <queue>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int loop, num;
	string str;
	queue<int> que;
	cin >> loop;

	for (int i = 0; i < loop; ++i)
	{

		cin >> str;

		if (str == "push")
		{
			cin >> num;
			que.push(num);
		}
		else if (str == "pop")
		{
			if (que.empty())
			{
				cout << -1 << '\n';
				continue;
			}
			cout << que.front() << '\n';
			que.pop();
		}
		else if (str == "front")
		{
			if (que.empty())
			{
				cout << -1 << '\n';
				continue;
			}
			cout << que.front() << '\n';
		}
		else if (str == "back")
		{
			if (que.empty())
			{
				cout << -1 << '\n';
				continue;
			}
			cout << que.back() << '\n';
		}
		else if (str == "size")
			cout << que.size() << '\n';
		else if (str == "empty")
			cout << que.empty() << '\n';
	}
}
