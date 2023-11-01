#include <string>
#include <set>
#include <iostream>

using namespace std;

int main() {
    set <string> s;
    int N;

    cin >> N;

    while (N--) {
        string tmp1;
        string tmp2;

        cin >> tmp1 >> tmp2;

        if (tmp2 == "enter") {
            s.insert(tmp1);
        }
        else {
            s.erase(tmp1);
        }
    }

    for (auto it = s.rbegin(); it != s.rend(); it++) {
        cout << *it << '\n';
    }


    return 0;
}
