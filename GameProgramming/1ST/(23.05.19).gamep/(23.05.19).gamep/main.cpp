#include<iostream>
#include "Core.h"
using namespace std;

int main()
{
	if (!Core::GetInst()->Init())
	{
		cout << "게임 초기화 실패\n";
		Core::DestroyInst();
		return 0;
	}
	Core::GetInst()->Run();
	Core::DestroyInst();
}
