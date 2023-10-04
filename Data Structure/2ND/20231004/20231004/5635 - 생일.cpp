#include <iostream>
#include <queue>

using namespace std;

int main()
{
	priority_queue <pair<int, string>> pq1;
	priority_queue <pair<int, string>, vector<pair<int, string>>, greater<>> pq2;
	string str;
	int loop, input1, input2, input3, index = 0;

	cin >> loop;

	while (loop--)
	{
		cin >> str >> input1 >> input2 >> input3;
		index = input1;
		index += input2 * 100;
		index += input3 * 10000;
		pq1.push(make_pair(index, str));
		pq2.push(make_pair(index, str));
	}

	cout << pq1.top().second << '\n' << pq2.top().second;
}
