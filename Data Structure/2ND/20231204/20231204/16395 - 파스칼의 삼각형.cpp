#include <iostream>

using namespace std;

int main()
{
    int n, k, arr[30][30];
    cin >> n >> k;

    arr[0][0] = 1;

    for (int i = 1; i < n; ++i)
    {
        arr[i][0] = arr[i - 1][0];
        for (int j = 1; j < i; ++j)
            arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
        arr[i][i] = arr[i - 1][i - 1];
    }

    cout << arr[n - 1][k - 1];
    return 0;
}