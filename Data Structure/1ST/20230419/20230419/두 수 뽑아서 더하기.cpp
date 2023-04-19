#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> numbers)
{
    vector<int> answer;
    vector<int> answer1;

    for (int i = 0; i < numbers.size(); ++i)
    {
        for (int j = 0; j < numbers.size(); ++j)
        {
            if (i == j)
                continue;
            answer1.push_back(numbers[i] + numbers[j]);
        }
    }


    for (int i = answer1.size() - 1; i > 0; --i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (answer1[j] > answer1[j + 1])
            {
                int temp = answer1[j];
                answer1[j] = answer1[j + 1];
                answer1[j + 1] = temp;
            }
        }
    }

    answer.push_back(answer1[0]);
    for (int i = 1; i < answer1.size(); ++i)
        if (answer[answer.size() - 1] != answer1[i])
            answer.push_back(answer1[i]);

    return answer;
}