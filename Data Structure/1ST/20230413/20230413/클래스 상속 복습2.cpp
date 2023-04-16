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
		cout << "¿ì¿Õ ÀüÈ­\n";
	}
	
	void receive()
	{
		cout << "¿ì¿Õ ÀüÈ­ ¹Þ¾Ò´ç\n";
	}

	void sendSMS()
	{
		cout << "¿ì¿Õ ¹®ÀÚ\n";
	}

	void doInternet()
	{
		cout << "¿ì¿Õ ÀÎÅÍ³Ý\n";
	}
};
