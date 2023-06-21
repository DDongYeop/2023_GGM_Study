#include <iostream>
#include <string>
#include <set>
#include <unordered_set>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    unordered_set<string> s1;
    set<string> s2;
    string name;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> name;
        s1.insert(name);
    }
    for (int i = 0; i < m; i++)
    {
        cin >> name;
        if (s1.find(name) != s1.end())
            s2.insert(name);
    }
    cout << s2.size() << '\n';
    for (auto itr : s2)
    {
        cout << itr << '\n';
    }
}
