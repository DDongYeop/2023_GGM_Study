#include <iostream>
using namespace std;

class Phone 
{
public:
	void call();
	void receive();
	void sendSMS();
};

class Computer 
{
public:
	void doInternet();
};

class SmartPhone : public Phone, public Computer
{
	void call()
	{
		cout << "��� ��ȭ\n";
	}
	
	void receive()
	{
		cout << "��� ��ȭ �޾Ҵ�\n";
	}

	void sendSMS()
	{
		cout << "��� ����\n";
	}

	void doInternet()
	{
		cout << "��� ���ͳ�\n";
	}
};
