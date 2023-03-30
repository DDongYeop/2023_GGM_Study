#include <iostream>
using namespace std;

class Complex
{
public:
	double real, imag;
	Complex(double real, double imag)
	{
		this->real = real;
		this->imag = imag;
	}
	void Print()
	{
		cout << real << " + " << imag << "i" << endl;
	}
};

Complex Add(const Complex& x, const Complex& y)
{
	Complex com(x.real + y.real, x.imag + y.imag);
	return com;
}

int main()
{
	Complex c1{ 1, 2 }, c2{ 3, 4 };
	Complex t = Add(c1, c2);
	t.Print();
}