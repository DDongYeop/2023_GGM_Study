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
	cout << "������⸦ �������� ���ڿ� 2���� �Է��Ͻÿ� : ";
	cin >> sx >> sy;
	cout << "������⸦ �������� �Ǽ� 2���� �Է��Ͻÿ� : ";
	cin >> fx >> fy;
	cout << "������⸦ �������� ���� 2���� �Է��Ͻÿ� : ";
	cin >> ix >> iy;

	Swap(sx, sy);
	Swap(ix, iy);
	Swap(fx, fy);

	cout << "Swap �Լ� ȣ�� �� ����Դϴ�.\n";
	cout << sx << ' ' << sy << '\n';
	cout << ix << ' ' << iy << '\n';
	cout << fx << ' ' << fy << '\n';
}
