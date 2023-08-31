#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main()
{
	int n, m, k, x, input1, input2, lastIndex, index = 1;
	deque<int> deq;
	bool _isThere = false;
	vector<vector<int>> graph;
	vector<int> visited;
	cin >> n >> m >> k >> x;

	graph.resize(n + 1);
	visited.resize(n + 1, 0);
	lastIndex = x;

	while (m--)
	{
		cin >> input1 >> input2;
		graph[input1].push_back(input2);
	}

	deq.push_back(x);
	visited[deq.front()] = -1;
	while (!deq.empty())
	{
		for (auto i : graph[deq.front()])
		{
			if (visited[i] != 0)
				continue;
			deq.push_back(i);
			visited[i] = index;
		}

		if (lastIndex == deq.front())
		{
			lastIndex = deq.back();
			++index;
		}
		deq.pop_front();
	}

	for (int i = 1; i <= n; ++i)
	{
		if (visited[i] == k)
		{
			cout << i << '\n';
			_isThere = true;
		}
	}
	if (!_isThere)
		cout << "-1";
}
