#include<iostream>
#include "Core.h"
using namespace std;

int main()
{
	if (!Core::GetInst()->Init())
	{
		cout << "���� �ʱ�ȭ ����\n";
		Core::DestroyInst();
		return 0;
	}
	Core::GetInst()->Run();
	Core::DestroyInst();
}
