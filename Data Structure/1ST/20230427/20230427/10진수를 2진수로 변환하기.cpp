#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

stack<int> stk;

void FindBinaryNumber(int num);

int main()
{
	int num;
	cout << "10진수 값을 입력하세요 : ";
	cin >> num;
	try
	{
		if (num < 0)
			throw '음수';
	}
	catch (char str)
	{
		cout << "양수를 입력하세요.";
	}

	cout << "2진수로 변환한 값 : ";
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
