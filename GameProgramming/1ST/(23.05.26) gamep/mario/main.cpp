#include<iostream>
#include "Core.h"
using namespace std;
int main()
{
	// Core 클래스를 초기화할거야.
	// 초기화가 안되었으면 main을 꺼버릴거야.
	if (!Core::GetInst()->Init())
	{
		cout << "게임 초기화 실패!" << endl;
		Core::DestroyInst();
		return 0;
	}
	// 게임 실행
	Core::GetInst()->Run();

	// GetInst() 동적할당 삭제
	Core::DestroyInst();
}