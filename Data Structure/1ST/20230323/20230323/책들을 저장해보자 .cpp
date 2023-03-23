#include <iostream>
using namespace std;

class Book
{
public:
	string name;
	int price;

	Book(string name, int price)
	{
		this->name = name;
		this->price = price;
	}
	void Print()
	{
		cout << "제목 : " << name << "\t가격 : " << price << '\n';
	}
};

int main()
{
	Book books[2]
	{
		Book("어서와 C#", 25000),
		Book("어서와 C++", 20000)
	};

	cout << "소장하고 있는 책 정보" << endl;
	cout << "====================" << endl;
	for (Book& b : books)
		b.Print();
	cout << "====================" << endl;
}