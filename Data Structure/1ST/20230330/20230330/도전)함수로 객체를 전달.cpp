#include<iostream>
using namespace std;

class  Pizza
{
	int radius;
public:
	Pizza(int r = 0) : radius(r)
	{

	}

	~Pizza()
	{

	}

	void SetRadius(int r)
	{
		radius = r; 
	}

	void Print()
	{
		cout << "Pizza(" << radius << ")" << endl;
	}
};

void Upgrade(Pizza& p)
{
	p.SetRadius(20);
}

void Upgrade(Pizza *p)
{
	p->SetRadius(20);
}

int main()
{
	Pizza obj(10);
	Upgrade(obj);
	Upgrade(&obj);
	obj.Print();
}
