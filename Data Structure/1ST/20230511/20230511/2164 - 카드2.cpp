#include <iostream>
#include <queue>
using namespace std;

int main()
{
	int input;
	queue<int> que;
	bool isTrash = true;
	cin >> input;

	for (int i = 1; i <= input; ++i)
	{
		que.push(i);
	}

	while (que.size() != 1)
	{
		if (isTrash)
			que.pop();
		else
		{
			que.push(que.front());
			que.pop();
		}
		isTrash = !isTrash;
	}

	cout << que.front();
	
	return 0;
}
