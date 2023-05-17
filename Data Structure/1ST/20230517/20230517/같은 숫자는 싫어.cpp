#include <vector>
#include <iostream>
#include <queue>

using namespace std;

vector<int> solution(vector<int> arr)
{
    vector<int> answer;
    queue<int> que;

    for (int i = 0; i < arr.size(); ++i)
    {
        if (que.empty())
            que.push(arr[i]);
        else if (que.back() != arr[i])
            que.push(arr[i]);
    }

    int index = que.size();
    for (int i = 0; i < index; ++i)
    {
        answer.push_back(que.front());
        que.pop();
    }

    return answer;
}
