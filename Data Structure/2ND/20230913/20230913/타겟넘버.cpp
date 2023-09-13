#include <string>
#include <vector>

using namespace std;

int answer = 0;
int targetIndex = 0;
void DFS(vector<int> numbers, int index);

int solution(vector<int> numbers, int target) 
{
    targetIndex = target;
    DFS(numbers, 0);
    return answer;
}

void DFS(vector<int> numbers, int index)
{
    if (index == numbers.size())
    {
        int total = 0;
        for (int i : numbers)
            total += i;
        if (total == targetIndex)
             ++answer;
        return;
    }

    DFS(numbers, index+1);
    numbers[index] *= -1;
    DFS(numbers, index+1);
}
