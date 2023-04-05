#include <iostream>
using namespace std;

class Myclass
{
	int x;
	char c;
	string s;

	Myclass(const Myclass& myclass)
	{
		this->x = myclass.x;
		this->c = myclass.c;
		this->s = myclass.s;
	}
};
