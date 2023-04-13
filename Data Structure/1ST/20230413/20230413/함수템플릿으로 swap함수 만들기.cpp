#include <iostream>
using namespace std;
template<class T>

void Swap(T &x, T &y)
{
	T temp = x;
	x = y;
	y = temp;
}

int main()
{
	string sx, sy;
	float fx, fy;
	int ix, iy;
	cout << "띄워쓰기를 기준으로 문자열 2개를 입력하시오 : ";
	cin >> sx >> sy;
	cout << "띄워쓰기를 기준으로 실수 2개를 입력하시오 : ";
	cin >> fx >> fy;
	cout << "띄워쓰기를 기준으로 정수 2개를 입력하시오 : ";
	cin >> ix >> iy;

	Swap(sx, sy);
	Swap(ix, iy);
	Swap(fx, fy);

	cout << "Swap 함수 호출 후 결과입니다.\n";
	cout << sx << ' ' << sy << '\n';
	cout << ix << ' ' << iy << '\n';
	cout << fx << ' ' << fy << '\n';
}
