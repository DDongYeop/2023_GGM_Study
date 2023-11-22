#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long>tree;

long long binarySearch(long long n, long long m);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    long long n, m, input;

    cin >> n >> m;
    tree.resize(n);

    while (n--)
    {
        cin >> input;
        tree.push_back(input);
    }

    sort(tree.begin(), tree.end());
    cout << binarySearch(tree.back(), m);
}

long long binarySearch(long long n, long long m)
{
    long long left = 1, right = n, cutting, sum;
    while (left <= right)
    {
        cutting = (left + right) / 2;
        sum = 0;
        for (long long k : tree)
        {
            if (k > cutting)
                sum += k - cutting;
        }

        if (sum >= m)
            left = cutting + 1;
        else // 
            right = cutting - 1;
    }
    return right;
}
