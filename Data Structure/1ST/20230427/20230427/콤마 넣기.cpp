#include <iostream>
#include <stack>
using namespace std;

int main()
{
	int num;
	stack<char> stk;
	string str;
	cin >> str;

	for (int i = str.size()-1; i >= 0; --i)
	{
		if ((str.size() - 1 - i) % 3 == 0 && i != str.size()-1)
			stk.push(',');
		stk.push(str[i]);
	}
	num = stk.size();
	for (int i = 0; i < num; ++i)
	{
		cout << stk.top();
		stk.pop();
	}
}
