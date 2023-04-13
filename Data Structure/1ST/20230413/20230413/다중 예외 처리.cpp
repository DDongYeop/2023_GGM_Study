#include <iostream>
using namespace std;

int main()
{
	int age;
	while (true)
	{
		try
		{
			cout << "나이를 입력하세용 !! \n";
			cin >> age;
			if (age < 0)
				throw age;
			else if (age >= 120)
				throw 'c';
			else if (25 <= age)
				throw 1.1f;
			cout << age << "세로 청소년입미다 !!";
			break;
		}
		catch (int age)
		{
			cout << "양수를 입력하세요\n";
			continue;
		}
		catch (float f)
		{
			cout << "청소년이 아닙니다\n";
			continue;
		}
		catch (char ch)
		{
			cout << "다시입력하세영\n";
			continue;
		}
	}
}