#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    int index = 0, past;

    for (int i = 0; i < progresses.size(); ++i)
    {
        progresses[i] += speeds[i] * past;

        while (progresses[i] < 100)
        {
            ++index;
            progresses[i] += speeds[i];
        }

        if (answer.empty())
            answer.push_back(1);
        else if (index == past)
            answer[answer.size() - 1] += 1;
        else
            answer.push_back(1);
        past = index;
    }

    return answer;
}