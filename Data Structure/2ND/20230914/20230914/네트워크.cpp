#include <vector>

using namespace std;

vector<int> visited;
int index;
vector<vector<int>> computer;

void DFS(int index);

int solution(int n, vector<vector<int>> computers) 
{
    int answer = 0;
    visited.resize(n + 1, 0);
    computer = computers;
    index = n;

    for (int i = 0; i < computers[0].size(); ++i)
    {
	    if (visited[i] != 0)
            continue;

        ++answer;
        visited[i] = 1;
        DFS(i);
    }
    
    return answer;
}

void DFS(int idx)
{
    for (int i = 0; i < computer.size(); ++i)
    {
        if (computer[i][idx] == 0)
            continue;

        for (int j = 0; j < computer[0].size(); ++j)
        {
            if (computer[i][j] == 0)
                continue;
            if (visited[j] != 0)
                continue;;
            visited[j] = 1;
            DFS(j);
        }
    }
}
