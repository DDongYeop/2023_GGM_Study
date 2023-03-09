#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	cout << "영문자를 입력하고 \'1\'을 치세요" << endl;
	int vowel=0, consonant=0;
	int index = 0;

	while (true)
	{
		char ch;
		cin >> ch;
		if (ch == '1')
			break;
		
		switch (ch)
		{
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
			vowel++;
			break;
		default:
			consonant++;
			break;
		}

	}

	cout << "모음 : " << vowel << endl << "자음 : " << consonant;
}