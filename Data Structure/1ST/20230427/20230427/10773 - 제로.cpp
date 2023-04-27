#include <iostream>
#include <stack>
using namespace std;

int main()
{
	int num, index;
	stack<int> stk;
	cin >> num;

	for (int i = 0; i < num; ++i)
	{
		cin >> index;
		if (index == 0 && stk.top() != 0)
			stk.pop();
		else
			stk.push(index);
	}
	num = stk.size();
	index = 0;
	for (int i = 0; i < num; ++i)
	{
		index += stk.top();
		stk.pop();
	}
	cout << index;

	return 0;
}
