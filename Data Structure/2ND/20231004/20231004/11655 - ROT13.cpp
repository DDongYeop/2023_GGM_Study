#include <iostream>
#include <string>

using namespace std;

int main()
{
	string str;
	getline(cin, str);

	for (char c : str)
	{
		if (c < 65)
			cout << c;
		else
		{
			if (c < 91)
			{
				if (c < 78)
					cout << (char)(c + 13);
				else 
					cout << (char)(c - 13);
			}
			else
			{
				if (c < 110)
					cout << (char)(c + 13);
				else
					cout << (char)(c - 13);
			}
		}
	}
}
