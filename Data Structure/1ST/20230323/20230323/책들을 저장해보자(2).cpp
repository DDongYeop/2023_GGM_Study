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
		cout << "제목 : " << name << "\t가격 : " << price << '\n';
	}
};

int main()
{
	string str;
	int num, price;
	cout << "총 몇권의 책을 저장하고 싶으신가요? : ";
	cin >> num;
	Book *books = new Book[num];
	cout << "책의 이름과 가격을 띄워쓰기 기준으로 입력하세요. \n";
	for (int i = 0; i < num; ++i)
	{
		cin >> str >> price;
		books[i].name = str;
		books[i].price = price;
	}
	cout << "소장하고 있는 책 정보" << endl;
	cout << "====================" << endl;
	for (int i = 0; i < num; ++i)
		books[i].Print();
	cout << "====================" << endl;

	delete[] books;
}