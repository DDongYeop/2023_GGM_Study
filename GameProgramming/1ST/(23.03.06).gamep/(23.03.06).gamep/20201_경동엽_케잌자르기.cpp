#include <iostream>

using namespace std;

int main()
{
	int a, b, c, d;
	bool fir = false, sec = false;

	cin >> a >> b >> c >> d;

	if (a >= c && c <= b)
		fir = true;
	else if (a <= c && c >= b)
		fir = true;
	if (a >= d && d <= b)
		sec = true;
	else if (a <= d && d >= b)
		sec = true;

	if (fir != sec)
		cout << "cross";
	else
		cout << "not cross";
}
