#include <iostream>
#include <string>

using namespace std;

int main()
{
	string str;
	cout << "주민등록번호를 입력하시오 : ";
	cin >> str;
	str.erase(str.find("-"), 1);
	cout << "-가 제거된 주민등록번호 : " << str;
}