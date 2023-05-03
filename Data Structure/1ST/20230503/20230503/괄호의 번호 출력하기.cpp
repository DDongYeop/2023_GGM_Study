#include <iostream>
#include <stack>
using namespace std;

int main()
{
	int open = 0;
	string str;
	stack<int> stk;
	cout << "수식      : ";
	cin >> str;
	cout << "괄호 번호 : ";
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] == '(')
		{
			++open;
			stk.push(open);
			cout << open;
		}
		else if (str[i] == ')')
		{
			cout << stk.top();
			stk.pop();
		}
	}
}
