#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int index;
    queue<pair<int, int>> q;

    cin >> index;
    q.push(make_pair(index, 0));

    while (!q.empty())
    {
        if (q.front().first == 1)
            break;

        if (q.front().first % 2 == 0)
            q.push(make_pair(q.front().first / 2, q.front().second + 1));
        if (q.front().first % 3 == 0)
            q.push(make_pair(q.front().first / 3, q.front().second + 1));
        q.push(make_pair(q.front().first - 1, q.front().second + 1));
        q.pop();
    }

    cout << q.front().second;
}
