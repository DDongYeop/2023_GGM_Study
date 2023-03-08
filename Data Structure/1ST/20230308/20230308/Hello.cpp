#include <iostream>
#include <string>

using namespace std;

int main()
{
	string name, pos;
	cout << "이름을 입력하시오 : ";
	cin >> name;
	cout << "주소를 입력하시오 : ";
	cin.ignore();
	getline(cin, pos);
	cout << pos << "의 " << name << "씨 안녕하세요?";
}