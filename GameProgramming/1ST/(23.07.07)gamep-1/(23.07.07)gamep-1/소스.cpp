#include <iostream>

//typedef: �ڷ�{Ÿ��)�� ������ �ϴ� ģ�� | POS, * PPOS ��� �θ��� 
typedef struct _tagpos
{
	int x;
	int y;
}POS, * PPOS;

typedef int INT;
typedef int* INTPTR;

//Ÿ���� ������
typedef int (FUNC_PTR)(int, int);
typedef int (FUNC_PTR2)(int);

// C++ Modern
using namespace std;
using FUNC_TYPE = int(int, int);

//�ϳ��ϳ� �ϴ½�
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
	int m_itemid; // �� 
};

int main()
{
	/*
	typedef int ia;
	ia ab = 10;

	int a = 10;
	// [ �ּ� ] ----> [     ]
	//  ������
	int* ptr = &a;
	*ptr = 15;
	*/

	/*
	//���� �޸𸮿� ������
	int a;
	float b; 

	FUNC_PTR t;
	t(1, 2);
	*/

	FUNC_PTR* fn;
	fn = Add; // Sub�� �ٲٸ� SUb�� ��� �ȴ�

	//�ΰ� ���� �� ���
	int result = fn(1, 2);
	int result2 = (*fn)(1, 2);
	int result = Add(1, 2);

	cout << result << '\n'; //Add ������� ���´�
	cout << result2 << '\n'; //Add ������� ���´� | �Լ� �����ʹ� ������ �ٿ��� �Ȱ���. 
	cout << Add << '\n'; //Add �ּҰ��� ���´�
}
