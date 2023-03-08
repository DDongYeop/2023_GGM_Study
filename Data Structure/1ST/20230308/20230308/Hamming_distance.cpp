#include <iostream>
#include <string>

using namespace std;

int main()
{
	string str1, str2;
	int index = 0;
	cout << "DNA1 : ";
	cin >> str1;
	cout << "DNA2 : ";
	cin >> str2;

	for (int i = 0; i < str1.size(); i++)
		if (str1[i] != str2[i])
			index++;

	cout << "해밍 거리는 " << index;
}