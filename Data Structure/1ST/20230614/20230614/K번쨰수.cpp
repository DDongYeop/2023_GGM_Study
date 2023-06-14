#include <string>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) 
{
    vector<int> answer;

    for (int i = 0; i < commands.size(); ++i)
    {
        vector<int> sort;
        for (int j = commands[i][0] - 1; j < commands[i][1]; ++j)
            sort.push_back(array[j]);

        stable_sort(sort.begin(), sort.end());
        answer.push_back(sort[commands[i][2] - 1]);
    }

    return answer;
}