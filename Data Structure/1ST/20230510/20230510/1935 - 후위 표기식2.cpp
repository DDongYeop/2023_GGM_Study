#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main()
{
	int input;
	string str;
	stack<double> stk;
	cin >> input >> str;

	vector<double> vec;

	for (int i = 0; i < input; ++i)
	{
		double num;
		cin >> num;
		vec.push_back(num);
	}

	for (int i = 0; i < str.size(); ++i)
	{
		switch (str[i])
		{
		case '+':
		{
			double x = stk.top();
			stk.pop();
			double y = stk.top();
			stk.pop();
			stk.push(y + x);
		} break;
		case '-':
		{
			double x = stk.top();
			stk.pop();
			double y = stk.top();
			stk.pop();
			stk.push(y - x);
		} break;
		case '*':
		{
			double x = stk.top();
			stk.pop();
			double y = stk.top();
			stk.pop();
			stk.push(y * x);
		} break;
		case '/':
		{
			double x = stk.top();
			stk.pop();
			double y = stk.top();
			stk.pop();
			stk.push(y / x);
		} break;
		default:
			stk.push(vec[str[i] - 65]);
			break;
		}
	}

	cout << fixed;
	cout.precision(2);
	cout << stk.top();
}
