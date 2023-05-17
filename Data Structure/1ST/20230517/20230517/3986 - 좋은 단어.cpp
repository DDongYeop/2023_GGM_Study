#include<iostream>
#include<stack>
using namespace std;

int main()
{
	int input, num = 0;;
	string str;
	cin >> input;

	for (int i = 0; i < input; ++i)
	{
		cin >> str;
		stack<char> stk;

		for (int j = 0; j < str.size(); ++j)
		{
			if (stk.empty())
				stk.push(str[j]);
			else if (stk.top() == str[j])
				stk.pop();
			else
				stk.push(str[j]);
		}

		while (stk.size() > 1)
		{
			int index = stk.top();
			stk.pop();
			if (stk.top() == index)
				stk.pop();
			else
				break;
		}
		
		if (stk.empty())
			++num;
	}

	cout << num;
}
