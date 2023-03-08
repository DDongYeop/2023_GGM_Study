#include <iostream>

using namespace std;

int main()
{
	int thisMoney, price;

	cout << "현재 가지고 있는 돈 : ";
	cin >> thisMoney;
	cout << "캔디의 가격 : ";
	cin >> price;
	cout << "최대로 살 수 있는 캔디의 개수 = " << thisMoney / price << "\n";
	cout << "캔디 구입 후 남은 돈 = " << thisMoney % price << endl;
}