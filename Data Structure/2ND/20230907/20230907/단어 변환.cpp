#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

bool LanguageCheck(string begin, string end);

int solution(string begin, string target, vector<string> words) 
{
    int answer = 0;

    unordered_map<string, int> um;
    queue<string> q;

    um.insert(make_pair(begin, 0));
    for (int i = 0; i < words.size(); ++i)
        um.insert(make_pair(words[i], 0));

    q.push(begin);

    while (!q.empty())
    {
        string str = q.front();
        q.pop();

        for (int i = 0; i < words.size(); ++i)
        {
            if (um[words[i]] != 0)
                continue;

            if (!LanguageCheck(str, words[i]))
                continue;

            um[words[i]] = um[str] + 1;
            q.push(words[i]);
        }
    }

    return um[target];
}

bool LanguageCheck(string begin, string end)
{
    int cnt = 0;

    for (int i = 0; i < begin.size(); ++i)
    {
        if (begin[i] != end[i])
        {
            ++cnt;
            if (cnt > 1)
                return false;
        }
    }
    if (cnt == 1)
        return true;
    return false;
}
