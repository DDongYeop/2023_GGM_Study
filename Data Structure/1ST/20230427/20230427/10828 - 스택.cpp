#include <iostream>
#include <stack>
using namespace std;

int main()
{
	int num, index;
	stack<int> st;
	string str;
	cin >> num;
	for (int i = 0; i < num; ++i)
	{
		cin >> str;
		if (str == "push")
		{
			cin >> index;
			st.push(index);
		}
		else if (str == "pop")
		{
			if (st.size() == 0)
			{
				cout << "-1" << '\n';
				continue;
			}
			cout << st.top() << '\n';
			st.pop();
		}
		else if (str == "top")
		{
			if (st.size() == 0)
			{
				cout << "-1" << '\n';
				continue;
			}
			cout << st.top() << '\n';
		}
		else if (str == "empty")
			cout << st.empty() << '\n';
		else if (str == "size")
			cout << st.size() << '\n';
	}
}
