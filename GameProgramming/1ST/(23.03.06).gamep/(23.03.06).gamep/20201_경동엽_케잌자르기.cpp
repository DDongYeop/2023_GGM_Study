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


// 사실 a와 b 사이에 c,d 중 딱 하나 있다면 cross가 되는거고,
// 만약에 둘다 있거나 하나도 없다면 not cross가 되는것이다. 