#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
	int loop, input1, input2, front;
	cin >> loop;
	vector<vector<int>> graph(loop + 1);
	vector<int> visited(loop + 1, -1);
	queue<int> q;

	for (int i = 1; i < loop; ++i)
	{
		cin >> input1 >> input2;
		graph[input1].push_back(input2);
		graph[input2].push_back(input1);
	}

	q.push(1);

	while (!q.empty())
	{
		front = q.front();
		q.pop();

		for (auto i : graph[front])
		{
			if (visited[i] != -1)
				continue;

			visited[i] = front;
			q.push(i);
		}
	}

	for (int i = 2; i < visited.size(); ++i)
		cout << visited[i] << '\n';
}
