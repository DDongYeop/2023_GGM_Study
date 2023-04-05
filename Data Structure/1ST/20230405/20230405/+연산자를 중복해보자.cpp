#include <iostream>
#include <string>
using namespace std;

class MyVector
{
private:
	double x, y;
public:
	MyVector(double x  = 0.0, double y = 0.0) : x{x}, y{y} {}
	string toString()
	{
		return "(" + to_string(x) + ")" + to_string(y) + ")";
	}
	MyVector operator + (const MyVector& v2)
	{
		MyVector temp;
		temp.x += x + v2.x;
		temp.y += y += v2.y;
		return *this;
	}
};