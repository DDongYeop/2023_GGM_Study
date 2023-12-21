#include <iostream>

using namespace std;

int main()
{
	string numberStrs[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	string numberInts[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	string str;
	cin >> str;

	for (int i = 0; i < 10; ++i)
	{
		while (true)
		{
			auto pos = str.find(numberStrs[i]);
			if (pos == string::npos)
				break;
			str.replace(pos, numberStrs[i].length(), numberInts[i]);
		}
	}

	cout << str;
}
