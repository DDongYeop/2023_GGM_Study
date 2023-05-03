#include <iostream>
#include <stack>
#include <Windows.h>
using namespace std;

void BracketTest(stack<int>& stk, int index);

int main()
{
    string str;
    stack<int> stk;

    cin >> str;

    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] == '{')
            stk.push(1);
        else if (str[i] == '[')
            stk.push(2);
        else if (str[i] == '(')
            stk.push(3);
        else if (str[i] == '}')
            BracketTest(stk, 1);
        else if (str[i] == ']')
            BracketTest(stk, 2);
        else if (str[i] == ')')
            BracketTest(stk, 3);
    }

    if (stk.size() == 0)
        cout << "��ȣ �˻� ����";
    else
        cout << "��ȣ �˻� ����";
}

void BracketTest(stack<int>& stk, int index)
{
    if (stk.empty() || stk.top() != index)
    {
        cout << "��ȣ �˻� ����";
        exit(1);
    }
    stk.pop();
}