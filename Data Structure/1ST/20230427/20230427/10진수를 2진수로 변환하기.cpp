#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

stack<int> stk;

void FindBinaryNumber(int num);

int main()
{
	int num;
	cout << "10���� ���� �Է��ϼ��� : ";
	cin >> num;
	try
	{
		if (num < 0)
			throw '����';
	}
	catch (char str)
	{
		cout << "����� �Է��ϼ���.";
	}

	cout << "2������ ��ȯ�� �� : ";
	FindBinaryNumber(num);
	num = stk.size();
	for (int i = 0; i < num; ++i)
	{
		cout << stk.top();
		stk.pop();
	}
}

void FindBinaryNumber(int num)
{
	if (num == 0)
		return;
	else if (num % 2 == 0)
		stk.push(0);
	else
		stk.push(1);
	FindBinaryNumber(floor(num * .5f));
}
