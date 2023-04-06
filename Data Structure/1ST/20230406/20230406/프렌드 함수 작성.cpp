#include <iostream>
using namespace std;

class Complex 
{
public:
	Complex(double r = 0.0, double i = 0.0) : real{ r }, imag{ i } { }
	void Print() 
	{
		cout << real << " + " << imag << "i" << endl;
	}
private:
	friend Complex Add(Complex com1, Complex com2);
	double real, imag;
};

Complex Add(Complex com1, Complex com2)
{
	Complex com(com1.real + com2.real, com1.imag + com2.imag);
	return com;
}

int main() {
	Complex c1(1, 2), c2(3, 4);
	Complex c3 = Add(c1, c2);
	c3.Print();
}