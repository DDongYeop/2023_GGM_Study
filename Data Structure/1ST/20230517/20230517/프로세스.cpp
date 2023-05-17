#include <string>
#include <vector>
#include <queue>

using namespace std;

int BigNum(queue<int> que, int findNum);

int solution(vector<int> priorities, int location)
{
    int answer = 1;
    int findNum = 0;
    queue<int> que;

    for (int i = 0; i < priorities.size(); ++i)
    {
        if (i == location)
        {
            que.push(-1);
            findNum = priorities[i];
        }
        else
            que.push(priorities[i]);
    }

    while (true)
    {
        int bigNum = BigNum(que, findNum);
        for (int i = 0; i <= que.size(); ++i)
        {
            if (findNum == bigNum)
                if (que.front() == -1)
                    return answer;
            if (que.front() == bigNum)
            {
                que.pop();
                ++answer;
                break;
            }
            else
            {
                que.push(que.front());
                que.pop();
            }
        }
    }

    return answer;
}

int BigNum(queue<int> que, int findNum)
{
    int big = findNum;
    int loop = que.size();

    for (int i = 0; i <= loop; ++i)
    {
        int index = que.front();
        if (index > big)
            big = index;
        que.push(que.front());
        que.pop();
    }
    return big;
}
