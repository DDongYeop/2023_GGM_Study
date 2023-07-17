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
	Item() : m_itemid(0), m_rarity(0), m_userid(0) {}
public:
	int m_itemid; // ������ ���̵�
	int m_rarity; // ������ ���
	int m_userid; // ������ ����id
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
		//� ���� �����ϸ� return
		if (_select(item, 2))
			return item;
	}
	return nullptr;
}

// �Լ���ü, ����,functional 

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
	//int result = fn(1, 2);
	int result2 = (*fn)(1, 2);
	int result = Add(1, 2);

	cout << result << '\n'; //Add ������� ���´�
	cout << result2 << '\n'; //Add ������� ���´� | �Լ� �����ʹ� ������ �ٿ��� �Ȱ���. 
	cout << Add << '\n'; //Add �ּҰ��� ���´�
}
