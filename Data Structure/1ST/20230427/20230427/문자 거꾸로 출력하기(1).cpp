#include <iostream>
#include <stack>
using namespace std;

int main()
{
	stack<char> s1;
	string str;
	cin >> str;
	for (int i = 0; i < str.size(); ++i)
		s1.push(str[i]);

	while (!s1.empty())
	{
		cout << s1.top();
		s1.pop();
	}
}
