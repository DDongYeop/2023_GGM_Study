#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main()
{
	string str;
	bool isEnd = false;

	while (getline(cin, str))
	{
		isEnd = false;

		stack<bool> bracket; //()

		if (str[0] == '.')
			return 0;

		for (int i = 0; i < str.size(); ++i)
		{
			if (str[i] == '(')
				bracket.push(true);
			else if (str[i] == ')')
			{
				if (bracket.size() == 0 || bracket.top() != true)
				{
					isEnd = true;
					break;
				}
				bracket.pop();
			}
			else if (str[i] == '[')
				bracket.push(false);
			else if (str[i] == ']')
			{
				if (bracket.size() == 0 || bracket.top() != false)
				{
					isEnd = true;
					break;
				}
				bracket.pop();
			}
		}
		
		if (!isEnd && bracket.size() == 0)
		{
			cout << "yes\n";
			continue;
		}
		else
		{
			cout << "no\n";
			continue;
		}
	}
	return 0; 
}
