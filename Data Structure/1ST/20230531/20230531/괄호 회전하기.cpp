#include <string>
#include <vector>
#include <queue>

using namespace std;

int CorrectParentheses(queue<char> que);

int solution(string s) 
{
    int answer = 0;
    queue<char> que;

    for (int i = 0; i < s.size(); ++i)
        que.push(s[i]);

    for (int i = 0; i < s.size(); ++i)
    {
        que.push(que.front());
        que.pop();
        answer += CorrectParentheses(que);
    }

    return answer;
}

int CorrectParentheses(queue<char> que)
{
    int size = que.size();
    string str;

    for (int i = 0; i < size; ++i)
    {
        switch (que.front())
        {
        case '(':
        case '[':
        case '{':
            str.push_back(que.front());
            break;
        case ')':
            if (str.size() == 0)
                return 0;
            if (str.back() == '(')
                str.pop_back();
            break;
        case ']':
            if (str.size() == 0)
                return 0;
            if (str.back() == '[')
                str.pop_back();
            break;
        case '}':
            if (str.size() == 0)
                return 0;
            if (str.back() == '{')
                str.pop_back();
            break;
        }
        que.pop();
    }

    if (str.size() == 0)
        return 1;
    return 0;
}
