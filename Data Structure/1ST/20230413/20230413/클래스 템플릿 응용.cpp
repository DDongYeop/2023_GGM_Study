#include <iostream>
using namespace std;
template<class T>
class Circle
{
private:
	T x, y, radius;

public:
	Circle(T t1, T t2, T t3) : x{ t1 }, y{ t1 }, radius{ t3 } {}
	
	T GetArea()
	{
		return radius * radius * PI;
	}

	static double const PI;
};

template<class T>
double const Circle<T>::PI = 3.14;

int main()
{
	Circle<int> c1{ 1,1,5 };
	Circle<double> c2{ 1.5, 1.5,5.0 };
	cout << c1.GetArea() << '\n';
	cout << c2.GetArea() << '\n';
}