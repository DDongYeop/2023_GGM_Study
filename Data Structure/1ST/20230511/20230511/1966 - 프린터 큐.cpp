#include <iostream>
#include <queue>
using namespace std;

int FindMaxValue(queue<int> que, int value);
void ResultPrint(queue<int> que, int value, int index);

int main()
{
	int loop;
	cin >> loop;

	int m, n;
	int input, value;

	for (int i = 0; i < loop; ++i)
	{
		cin >> m >> n;
		queue<int> que;
		for (int i = 0; i < m; ++i)
		{
			if (i == n)
			{
				cin >> value;
				que.push(-1);
			}
			else
			{
				cin >> input;
				que.push(input);
			}
		}
		ResultPrint(que, value, 1);
	}
}

int FindMaxValue(queue<int> que, int value)
{
	int maxNum = value;
	int num = que.size();
	for (int i = 0; i < num; ++i)
	{
		if (que.front() > maxNum)
			maxNum = que.front();
		que.pop();
	}
	return maxNum;
}

void ResultPrint(queue<int> que, int value, int index)
{
	int maxValue = FindMaxValue(que, value);
	while (true)
	{
		if (que.front() == -1 && value == maxValue)
		{
			cout << index << '\n';
			return;
		}
		else if (que.front() == maxValue)
		{
			que.pop();
			ResultPrint(que, value, ++index);
			return;
		}
		que.push(que.front());
		que.pop();
	}
}
