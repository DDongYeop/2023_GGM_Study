#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() 
{
    int n, input1, input2, cnt = 0;
    int lastT = 0;
    vector<pair<int, int>> v;
    cin >> n;

    while (n--)
    {
        cin >> input1 >> input2;
        v.push_back({ input2,input1 });
    }
    
    sort(v.begin(), v.end());
    
    for (int i = 0; i < v.size(); i++)
    {
        if (lastT <= v[i].second)
        {
            cnt++;
            lastT = v[i].first;
        }
    
    }
    cout << cnt;
}
