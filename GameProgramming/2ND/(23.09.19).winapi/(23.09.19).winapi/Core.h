#pragma once
//하나만 어디서든 쓸 수 있도록
//1학기에 했던 싱글톤 : 다이나믹 싱글톤 = 동적할당
//  장점 : 존재하지 않더라도 다시 생성 가능
//  단점 : 동적으로 할당하기에 제귀를 해줘야한다.
#include "define.h"

class Core
{
	SINGLE(Core);
};

