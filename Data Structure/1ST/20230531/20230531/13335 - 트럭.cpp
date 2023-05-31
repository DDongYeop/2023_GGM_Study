#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
	int n, bridge_length, weight, j, answer = 0, bridgeWeight = 0, weightIndex = 0, waitIndex = 0;
	vector<int> truck_weights;
	vector<int> wait;

	cin >> n >> bridge_length >> weight;
	for (int i = 0; i < n; ++i)
	{
		cin >> j;
		truck_weights.push_back(j);
	}

	while (true)
	{
		++answer;

		if (!wait.empty())
		{
			for (int i = 0; i < wait.size(); ++i)
			{
				++wait[i];
				if (wait[i] == bridge_length)
				{
					bridgeWeight -= truck_weights[waitIndex++];
				}
			}
		}
		
		if (truck_weights.size() > weightIndex)
		{
			if (bridgeWeight + truck_weights[weightIndex] <= weight)
			{
				wait.push_back(0);
				bridgeWeight += truck_weights[weightIndex];
				++weightIndex;
			}
		}

		if (truck_weights.size() - 1 <= weightIndex && wait[wait.size() - 1] >= bridge_length)
			break;
	}
	cout << answer;
}
