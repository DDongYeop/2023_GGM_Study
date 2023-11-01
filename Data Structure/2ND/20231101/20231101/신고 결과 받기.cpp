#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) 
{
    int index = 0;
    string str1, str2;
    vector<int> answer(id_list.size());
    unordered_map<string, tuple<unordered_set<string>, int, int>> um;
    unordered_set<string> us;

    for (auto str : id_list)
    {
        um.insert(make_pair(str, make_tuple(unordered_set<string>(), 0, index)));
        ++index;
    }

    for (auto str : report)
    {
        stringstream stream(str);
        stream >> str1 >> str2;

        if (get<0>(um[str1]).find(str2) == get<0>(um[str1]).end())
        {
            get<0>(um[str1]).insert(str2);
            get<1>(um[str2])++;
        }
    }

    for (auto p : um)
    {
        if (get<1>(p.second) >= k)
            us.insert(p.first);
    }

    for (auto p : um)
    {
        for (auto s : us)
        {
            if (get<0>(p.second).find(s) != get<0>(p.second).end())
                answer[get<2>(p.second)]++;
        }
        ++index;
    }

    return answer;
}
