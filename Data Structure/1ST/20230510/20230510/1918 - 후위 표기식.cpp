#include <iostream>
#include <stack>
using namespace std;

stack<char> stk;

void Operator(char ch);

int main()
{
	string str;
	cin >> str;

	for (int i = 0; i < str.size(); ++i)
	{
		switch (str[i])
		{
		case '(':
			stk.push('(');
			break;
		case '+':
		case '-':
		case '*':
		case '/':
		case ')':
			Operator(str[i]);
			break;
		default:
			cout << str[i];
			break;
		}
	}

	int index = stk.size();
	for (int i = 0; i < index; ++i)
	{
		cout << stk.top();
		stk.pop();
	}
}

void Operator(char ch)
{
	if (stk.empty())
	{
		stk.push(ch);
		return;
	}
	
	switch (ch)
	{
	case '+':
	case '-':
		if (stk.top() == '(')
		{
			stk.push(ch);
			return;
		}
		cout << stk.top();
		stk.pop();
		if (stk.empty())
			stk.push(ch);
		else
			Operator(ch);
		break;
	case '*':
	case '/':
		if (stk.top() == '+' || stk.top() == '-' || stk.top() == '(')
			stk.push(ch);
		else
		{
			cout << stk.top();
			stk.pop();
			Operator(ch);
		}
		break;
	case ')':
	{
		int index = stk.size();
		for (int i = 0; i < index; ++i)
		{
			if (stk.top() == '(')
			{
				stk.pop();
				break;
			}
			cout << stk.top();
			stk.pop();
		}
	} break;
	}
}
