#include <iostream>
using namespace std;


class Human 
{
protected:
	string name;
	int age;
public:
	Human(string name, int age) : name{ name }, age{ age } {}

	void Print()
	{
		cout << name << ": " << age << "¼¼\n";
	}
};

class Student : public Human
{
	string najor;

	Student(string name, int age) : Human(name, age) {}
};

int main()
{
	Human human1("ÃáÇâ", 18);
	Human human2("¸ù·æ", 21);

	human1.Print();
	human2.Print();
}
