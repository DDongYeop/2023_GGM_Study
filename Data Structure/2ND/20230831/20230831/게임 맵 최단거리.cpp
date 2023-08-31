#include <iostream>
#include <vector>
#include <deque>

using namespace std;

vector<vector<int>> map;
vector<vector<bool>> visited;

void QueueInput(deque<pair<int, int>>& q);

int solution(vector<vector<int>> maps)
{
    map = maps;
    int index = 1;
    deque<pair<int, int>> q;
    pair<int, int> lastPair = make_pair(0, 0);
    pair<int, int> endPair = make_pair(map.size() - 1, map[0].size() - 1);

    visited.resize(map.size() + 1);

    for (int i = 0; i < visited.size(); ++i)
        visited[i].resize(map[0].size(), false);

    q.push_back(make_pair(0, 0));
    visited[0][0] = true;

    while (!q.empty())
    {
        if (q.front() == endPair)
            return index;
        QueueInput(q);
        if (q.front() == lastPair)
        {
            lastPair = q.back();
            ++index;
        }
        q.pop_front();
    }
    return -1;
}

void QueueInput(deque<pair<int, int>>& q)
{
    pair<int, int> p = q.front();

    if (map.size() > p.first + 1 && !visited[p.first + 1][p.second])
    {
        if (map[p.first + 1][p.second] == 1)
        {
            q.push_back(make_pair(p.first + 1, p.second));
            visited[p.first + 1][p.second] = true;
        }
    }
    if (0 <= p.first - 1 && !visited[p.first - 1][p.second])
    {
        if (map[p.first - 1][p.second] == 1)
        {
            q.push_back(make_pair(p.first - 1, p.second));
            visited[p.first - 1][p.second] = true;
        }
    }
    if (map[0].size() > p.second + 1 && !visited[p.first][p.second + 1])
    {
        if (map[p.first][p.second + 1] == 1)
        {
            q.push_back(make_pair(p.first, p.second + 1));
            visited[p.first][p.second + 1] = true;
        }
    }
    if (0 <= p.second - 1 && !visited[p.first][p.second - 1])
    {
        if (map[p.first][p.second - 1] == 1)
        {
            q.push_back(make_pair(p.first, p.second - 1));
            visited[p.first][p.second - 1] = true;
        }
    }
}
