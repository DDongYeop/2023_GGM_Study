#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) 
{
	int n, j, answer = 0, bridgeWeight = 0, weightIndex = 0, waitIndex = 0;
	vector<int> wait;

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
	return answer;
}
