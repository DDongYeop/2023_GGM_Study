#include <iostream>
#include <stack>
using namespace std;

int main()
{
	int num = 0; 
	string str;
	cin >> num;

	for (int i = 0; i < num; ++i)
	{
		stack<bool> stk;
		cin >> str;
		for (int j = 0; j < str.size(); ++j)
		{
			if (str[j] == '(')
				stk.push(true);
			else if (str[j] == ')')
			{
				if (stk.size() == 0)
				{
					cout << "NO\n";
					break;
				}
				stk.pop();
			}
			if (j == str.size() - 1)
			{
				if (stk.size() == 0)
					cout << "YES\n";
				else if (stk.size() > 0)
					cout << "NO\n";
			}
		}
	}
}