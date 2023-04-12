#include <iostream>
using namespace std;


class Box 
{
private:
	double length;
	double width;
	double height;
	friend Box operator+(Box& v1, Box& v2);
	friend bool operator==(Box& v1, Box& v2);
	friend bool operator<(Box& v1, Box& v2);
public:
	static int count;
	Box(double length, double width, double height) : length{ length }, width{ width }, height{ height } 
	{
		++count;
	}

	double Volume() 
	{
		return length * width * height;
	}
};

int Box::count = 0;

int main(void) 
{
	Box Box1(1.0, 2.0, 3.0);
	Box Box2(1.0, 2.0, 5.0);
	cout << "ÀüÃ¼ °´Ã¼ ¼ö: " << Box::count << endl;
	return 0;
}

Box operator+(Box& v1, Box& v2)
{
	Box box(v1.length + v2.length, v1.width + v2.width, v1.height + v2.height);
	return box;
}

bool operator==(Box& v1, Box& v2)
{
	if (v1.length == v2.length && v1.width == v2.width && v1.height == v2.height)
		return true;
	else
		return false;
}

bool operator<(Box& v1, Box& v2)
{
	if (v1.length < v2.length && v1.width < v2.width && v1.height < v2.height)
		return true;
	else
		return false;
}
