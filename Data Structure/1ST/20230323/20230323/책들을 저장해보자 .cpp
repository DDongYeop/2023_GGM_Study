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
		cout << "���� : " << name << "\t���� : " << price << '\n';
	}
};

int main()
{
	Book books[2]
	{
		Book("��� C#", 25000),
		Book("��� C++", 20000)
	};

	cout << "�����ϰ� �ִ� å ����" << endl;
	cout << "====================" << endl;
	for (Book& b : books)
		b.Print();
	cout << "====================" << endl;
}