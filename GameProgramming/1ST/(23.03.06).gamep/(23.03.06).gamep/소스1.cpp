#include <iostream>

using namespace std;

int main()
{
	int a=0, b=0, c=0, d=0;
	bool fir = false, sec = false;

	cin >> a >> b;
	cin >> c >> d;

	if (a >= c && c <= b)
		fir = true;
	if (a >= d && d <= b)
		sec = true;

	if (fir == sec)
		cout << "cross";
	else
		cout << "not cross";

}
