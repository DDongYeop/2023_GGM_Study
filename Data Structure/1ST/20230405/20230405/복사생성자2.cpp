#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

class MyClass
{
public:
	MyClass(const char* str);
	~MyClass();
private:
	char* stored;

};

MyClass::MyClass(const char* str)
{
	stored = new char[strlen(str) + 1];
	strcpy(stored, str);
}

MyClass::~MyClass()
{
	delete[] stored;
}
