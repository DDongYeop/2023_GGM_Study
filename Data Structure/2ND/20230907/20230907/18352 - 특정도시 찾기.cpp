#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	int n, m, k, x, input1, input2;
	bool isPrint = false;
	vector<vector<int>> graph;
	vector<int> visited;
	queue<int> q;
	cin >> n >> m >> k >> x;

	graph.resize(n + 1);
	visited.resize(n + 1, -1);

	while (m--)
	{
		cin >> input1 >> input2;
		graph[input1].push_back(input2);
	}

	q.push(x);
	visited[x] = 0;

	while (!q.empty())
	{
		m = q.front();
		q.pop();

		for (int i : graph[m])
		{
			if (visited[i] != -1)
				continue;

			q.push(i);
			visited[i] = visited[m] + 1;
		}
	}

	for (int i = 1; i < graph.size(); ++i)
	{
		if (visited[i] == k)
		{
			cout << i << '\n';
			isPrint = true;
		}
	}
	if (!isPrint)
		cout << -1;
}
