#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	cout << "�����ڸ� �Է��ϰ� \'1\'�� ġ����" << endl;
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

	cout << "���� : " << vowel << endl << "���� : " << consonant;
}