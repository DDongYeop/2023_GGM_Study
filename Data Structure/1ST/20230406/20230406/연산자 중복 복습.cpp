#include <iostream>
using namespace std;

class Box
{
	double length;
	double width;
	double height;
public:
	Box()
	{
		length = width = height = 0;
	}
	Box (double l, double w, double h) : length{l}, width {w}, height {h}
	{
	}
	double GetVolume()
	{
		return length * width * height;
	}

	Box operator + (const Box& v2)
	{
		Box temp;
		temp.length += length + v2.length;
		temp.width += width + v2.width;
		temp.height += height + v2.height;
		return temp;
	}

	bool operator == (const Box& v2)
	{
		if (length == v2.length && width == v2.width && height == v2.height)
			return true;
		return false;
	}

	bool operator < (const Box& v2)
	{
		if (length < v2.length && width < v2.width && height < v2.height)
			return true;
		return false;
	}
};

int main()
{
	Box a(10, 10, 10), b(20, 20, 20), c;
	c = a + b;

	cout << c.GetVolume();
	cout << '\n';
	cout << (a == b);
	cout << '\n';
	cout << (a < b);
}