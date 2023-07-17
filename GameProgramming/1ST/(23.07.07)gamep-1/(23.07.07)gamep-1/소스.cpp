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
	Item() : m_itemid(0), m_rarity(0), m_userid(0) {}
public:
	int m_itemid; // 아이템 아이디
	int m_rarity; // 아이템 등급
	int m_userid; // 아이템 주인id
};

typedef bool (SELECTOR)(Item* _item, int index);

bool IsRareitem(Item* _item)
{
	return _item->m_rarity >= 3;
}

bool IsUserItem(Item* _item, int _userid)
{
	return _item->m_userid == _userid;
}

//Item* Finditem(Item _items[], int _itemcnt, int _itemid)
Item* Finditem(Item _items[], int _itemcnt, SELECTOR* _select)
{
	for (int i = 0; i < _itemcnt; i++)
	{
		Item* item = &_items[i];
		//어떤 조건 성립하면 return
		if (_select(item, 2))
			return item;
	}
	return nullptr;
}

// 함수객체, 람다,functional 

int main()
{
	Item items[10];
	items[2].m_itemid = 2;
	items[2].m_rarity = 4;
	//Item* selectitem = Finditem(items, 10, IsRareitem);
	Item* selectitem = Finditem(items, 10, IsUserItem);
	cout << selectitem->m_itemid << '\n';

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
	//int result = fn(1, 2);
	int result2 = (*fn)(1, 2);
	int result = Add(1, 2);

	cout << result << '\n'; //Add 결과값이 나온다
	cout << result2 << '\n'; //Add 결과값이 나온다 | 함수 포인터는 역참조 붙여도 똑같다. 
	cout << Add << '\n'; //Add 주소값이 나온다
}
