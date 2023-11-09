#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(int n, vector<int> times) 
{
    sort(times.begin(), times.end());
    long long left = times.front(), right = (long long)times.back() * n; // Ž�� ���� ���ϱ� // ��tims.front()�� �ȵɱ�?
    long long time, people, answer = 0;

    while (left <= right)
    {
        people = 0;
        time = (left + right) / 2;
        for (auto t : times)
            people += time / t; // �־��� �ð����� ä�� ���ִ� ��� �� ���ϱ�

        if (people >= n) // �־��� �ð����� n�� �̻� ä�� �� �ִٸ�
        {
            // ä�����ô�
            right = time - 1;
            answer = time;
        }
        else // �־��� �ð����� n���� ä��� ��ƴٸ�
            left = time + 1;// ä�����ô�  
    }
    return answer;
}
