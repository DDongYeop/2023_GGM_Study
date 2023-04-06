#include <iostream>
using namespace std;

class Time
{
	int hour, min, sec;
public:
	Time(int hour, int min, int sec)
	{
		this->hour = hour;
		this->min = min;
		this->sec = sec;
	}
	bool operator== (Time& t2)
	{
		if (hour == t2.hour && min == t2.min && sec == t2.sec)
			return true;
		return false;
	}
	bool operator!= (Time& t2)
	{
		if (hour == t2.hour && min == t2.min && sec == t2.sec)
			return false;
		return true;
	}
};


int main() 
{
	Time t1(1, 2, 3), t2(1, 2, 3);
	cout.setf(cout.boolalpha);
	cout << (t1 == t2) << endl;
	cout << (t1 != t2) << endl;
}