#include <iostream>
using namespace std;

class Book
{
public:
	string name;
	int price;

	Book() { }
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
	string str;
	int num, price;
	cout << "�� ����� å�� �����ϰ� �����Ű���? : ";
	cin >> num;
	Book *books = new Book[num];
	cout << "å�� �̸��� ������ ������� �������� �Է��ϼ���. \n";
	for (int i = 0; i < num; ++i)
	{
		cin >> str >> price;
		books[i].name = str;
		books[i].price = price;
	}
	cout << "�����ϰ� �ִ� å ����" << endl;
	cout << "====================" << endl;
	for (int i = 0; i < num; ++i)
		books[i].Print();
	cout << "====================" << endl;

	delete[] books;
}