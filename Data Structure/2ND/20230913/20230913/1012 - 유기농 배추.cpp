#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int t, m, n, k, input1, input2, cnt = 0;
    int addX[4] = { -1, 1, 0, 0 }, addY[4] = { 0, 0, -1, 1 };
    queue<pair<int, int>> q;
    cin >> t;

    while (t--)
    {
        cin >> m >> n >> k;
        vector<vector<int>> maps(m + 1, vector<int>(n + 1, 0));
        vector<vector<int>> visited(m + 1, vector<int>(n + 1, 0));
        q = queue<pair<int, int>>();
        cnt = 0;

        while (k--)
        {
            cin >> input1 >> input2;
            maps[input1][input2] = 1;
        }

        for (int i = 0; i <= m; ++i)
        {
            for (int j = 0; j <= n; ++j)
            {
                if (!maps[i][j] || visited[i][j])
                    continue;

                q.push(make_pair(i, j));
                visited[i][j] = 1;
                cnt++;
                while (!q.empty())
                {
                    int x = q.front().first;
                    int y = q.front().second;
                    for (int w = 0; w < 4; ++w)
                    {
                        int posX = addX[w] + x;
                        int posY = addY[w] + y;

                        if (posX < 0 || posY < 0)
                            continue;
                        if (posX > m || posY > n)
                            continue;
                        if (visited[posX][posY] || !maps[posX][posY])
                            continue;

                        visited[posX][posY] = 1;
                        q.push(make_pair(posX, posY));
                    }
                    q.pop();
                }
            }
        }
        cout << cnt << '\n';
    }
}
