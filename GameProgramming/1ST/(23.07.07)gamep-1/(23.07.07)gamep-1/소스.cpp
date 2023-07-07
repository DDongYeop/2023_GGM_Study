#include <iostream>

//typedef: 자료{타입)을 재정의 하는 친구 | POS, * PPOS 얘로 부른다 
typedef struct _tagpos
{
	int x;
	int y;
}POS, * PPOS;

typedef int INT;
typedef int* INTPTR;

//타입을 재정의
typedef int (FUNC_PTR)(int, int);
typedef int (FUNC_PTR2)(int);

// C++ Modern
using namespace std;
using FUNC_TYPE = int(int, int);

//하나하나 하는식
int(*fn)(int, int);

int Add(int a, int b)
{
	return a + b;
}

int Sub(int x, int y)
{
	return x - y;
}

class Item
{
public:
	int m_itemid; // 아 
};

int main()
{
	/*
	typedef int ia;
	ia ab = 10;

	int a = 10;
	// [ 주소 ] ----> [     ]
	//  포인터
	int* ptr = &a;
	*ptr = 15;
	*/

	/*
	//스택 메모리에 잡힌다
	int a;
	float b; 

	FUNC_PTR t;
	t(1, 2);
	*/

	FUNC_PTR* fn;
	fn = Add; // Sub로 바꾸면 SUb가 출력 된다

	//두개 같은 값 출력
	int result = fn(1, 2);
	int result2 = (*fn)(1, 2);
	int result = Add(1, 2);

	cout << result << '\n'; //Add 결과값이 나온다
	cout << result2 << '\n'; //Add 결과값이 나온다 | 함수 포인터는 역참조 붙여도 똑같다. 
	cout << Add << '\n'; //Add 주소값이 나온다
}
