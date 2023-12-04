#include <iostream>

using namespace std;

int main()
{
    int r, c, w, arr[31][31], cnt = 0;
    cin >> r >> c >> w;

    arr[0][0] = 1;

    for (int i = 1; i <= 30; ++i)
    {
        arr[i][0] = arr[i - 1][0];
        for (int j = 1; j < i; ++j)
            arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
        arr[i][i] = arr[i - 1][i - 1];
    }

    --r;
    for (int i = 0; i < w; ++i)
    {
        for (int j = 0; j <= i; ++j)
            cnt += arr[i + r][j];
    }

    cout << cnt;
    return 0;
}