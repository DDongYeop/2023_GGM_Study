#include<iostream>
#include "Core.h"
using namespace std;
int main()
{
	// Core Ŭ������ �ʱ�ȭ�Ұž�.
	// �ʱ�ȭ�� �ȵǾ����� main�� �������ž�.
	if (!Core::GetInst()->Init())
	{
		cout << "���� �ʱ�ȭ ����!" << endl;
		Core::DestroyInst();
		return 0;
	}
	// ���� ����
	Core::GetInst()->Run();

	// GetInst() �����Ҵ� ����
	Core::DestroyInst();
}