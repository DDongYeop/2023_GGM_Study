#include <iostream>
#include <string>

using namespace std;

int main()
{
	string str;
	cout << "�ֹε�Ϲ�ȣ�� �Է��Ͻÿ� : ";
	cin >> str;
	str.erase(str.find("-"), 1);
	cout << "-�� ���ŵ� �ֹε�Ϲ�ȣ : " << str;
}