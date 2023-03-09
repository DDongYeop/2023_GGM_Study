#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	int randomIndex = (rand() % 99) + 1;
	int index = 0, num = 0;

	while (1)
	{
		cout << "정답을 추측하여 보시오 : ";
		cin >> num;

		if (num > randomIndex)
			cout << "제시한 정수가 높습니다. " << endl;
		else if (num < randomIndex)
			cout << "제시한 정수가 낮습니다. " << endl;
		else
			break;
		index++;
	}

	cout << "축하합니다. 시도횟수 == " << index;
}