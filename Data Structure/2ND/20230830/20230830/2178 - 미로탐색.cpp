#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int n, m;
vector<vector<int>> map;
vector<vector<bool>> visited;

void QueueInput(deque<pair<int, int>>& q);

int main()
{
	int index = 1;
	string str;
	deque<pair<int, int>> q;
	pair<int, int> lastPair = make_pair(1, 1);
	cin >> n >> m;
	pair<int, int> endPair = make_pair(n, m);

	map.resize(n+1);
	visited.resize(n+1);

	for (int i = 1; i <= n; ++i)
	{
		cin >> str;
		map[i].push_back(0);
		for (char c : str)
			map[i].push_back(c != 48 ? true : false);

		visited[i].resize(m+1, false);
	}

	q.push_back(make_pair(1, 1));
	visited[q.front().first][q.front().second] = true;

	while (!q.empty())
	{
		if (q.front() == endPair)
		{
			cout << index;
			return 0;
		}
		QueueInput(q);
		if (q.front() == lastPair)
		{
			lastPair = q.back();
			++index;
		}
		q.pop_front();
	}
	cout << index;
}

void QueueInput(deque<pair<int, int>>& q)
{
	pair<int, int> p = q.front();

	if (n >= p.first + 1 && !visited[p.first + 1][p.second])
	{
		if (map[p.first + 1][p.second] == 1)
		{
			q.push_back(make_pair(p.first + 1, p.second));
			visited[p.first + 1][p.second] = true;
		}
	}
	if (1 <= p.first - 1 && !visited[p.first - 1][p.second])
	{
		if (map[p.first - 1][p.second] == 1)
		{
			q.push_back(make_pair(p.first - 1, p.second));
			visited[p.first - 1][p.second] = true;
		}
	}
	if (m >= p.second + 1 && !visited[p.first][p.second + 1])
	{
		if (map[p.first][p.second + 1] == 1)
		{
			q.push_back(make_pair(p.first, p.second + 1));
			visited[p.first][p.second + 1] = true;
		}
	}
	if (1 <= p.second - 1 && !visited[p.first][p.second - 1])
	{
		if (map[p.first][p.second - 1] == 1)
		{
			q.push_back(make_pair(p.first, p.second - 1));
			visited[p.first][p.second - 1] = true;
		}
	}
}
