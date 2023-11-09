#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(int n, vector<int> times) 
{
    sort(times.begin(), times.end());
    long long left = times.front(), right = (long long)times.back() * n; // 탐색 범위 정하기 // 왜tims.front()는 안될까?
    long long time, people, answer = 0;

    while (left <= right)
    {
        people = 0;
        time = (left + right) / 2;
        for (auto t : times)
            people += time / t; // 주어진 시간에서 채울 수있는 사람 수 구하기

        if (people >= n) // 주어진 시간에서 n명 이상 채울 수 있다면
        {
            // 채워봅시다
            right = time - 1;
            answer = time;
        }
        else // 주어진 시간에서 n명을 채우기 어렵다면
            left = time + 1;// 채워봅시다  
    }
    return answer;
}
