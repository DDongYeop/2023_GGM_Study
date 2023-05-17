#include<iostream>
#include<stack>
using namespace std;

int main()
{
	int input, input2;
	cin >> input;
	int index = 1;
	stack<int> stk;
	string str;

	for (int i = 0; i < input; ++i)
	{
		cin >> input2;

		if (stk.empty() || stk.top() > input2)
		{
			stk.push(input2);
			str += 'P';
		}
		else
		{
			while (true)
			{
				if (stk.top() > input2)
				{
					stk.push(input2);
					str += 'P';
					break;
				}
				else 
				{
					if (index != stk.top())
					{
						cout << "impossible";
						return 0;
					}
					stk.pop();
					str += 'O';
					++index;
				}

				if (stk.empty())
				{
					stk.push(input2);
					str += 'P';
					break;
				}
			}
		}
	}

	input = stk.size();
	for (int i = 0; i < input; ++i)
		str += 'O';

	cout << str;
}