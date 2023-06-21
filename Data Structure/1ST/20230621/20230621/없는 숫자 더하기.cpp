#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int solution(vector<int> numbers) 
{
    int answer = 0;
    unordered_set<int> s;

    for (auto a : numbers)
        s.insert(a);

    for (int i = 1; i < 10; ++i)
    {
        if (s.find(i) == s.end())
            answer += i;
    }

    return answer;
}
