#include <iostream>
#include <string>

using namespace std;

int main()
{
	string name, pos;
	cout << "�̸��� �Է��Ͻÿ� : ";
	cin >> name;
	cout << "�ּҸ� �Է��Ͻÿ� : ";
	cin.ignore();
	getline(cin, pos);
	cout << pos << "�� " << name << "�� �ȳ��ϼ���?";
}