#include <iostream>
#include <vector>

using namespace std;

//함수 객체 (Functor): 객체를 함수처럼 상요 
//람다 표현식(Lambda : 함수 객체가 한 쓰는데 1분걸리면 이거는 10초 걸림  

class Functor
{
public:
	void operator()(int _val)
	{
		cout << "함수 객체" << '\n';
		cout << m_val + _val << '\n';
	}

	Functor* operator+()
	{

	}
public:
	int m_val = 0;
};

void Test()
{
	cout << "김민수 바보" << '\n';
}

enum class ItemType
{
	None, Weapon, Armor
};

class Item
{
public:
	Item() = default;
 	Item(int _itemid, int _rarity, ItemType _type) : m_itemid(0), m_rarity(0), m_type(_type) {}
public:
	void test();
public:
	int m_itemid; // 아이템 아이디
	int m_rarity; // 아이템 등급
	ItemType m_type; // 아이템 주인id
};

typedef void (Item::*TEST_FUNC)();
class IsWeapon
{
public:
	bool operator()(Item& _item)
	{
		return _item.m_type == ItemType::Armor;
	}
};

class IsID
{
public:

public:
	bool operator()(Item& _item)
	{
		return _item.m_itemid == m_itemid;
	}
public:
	int m_itemid;
};

int main()
{
	vector<Item> v;
	Item i1;
	i1.m_itemid = 1;
	i1.m_rarity = 1;
	i1.m_type = ItemType::None;
	//v.push_back(i1);
	v.push_back(Item(1,1,ItemType::None));
	v.push_back(Item(2,10,ItemType::Weapon));
	v.push_back(Item(3,100,ItemType::Armor));
	int itemid = 3;
	auto lambdaitem = [](Item& _item) {return _item.m_type == ItemType::Armor;  };
	auto findItem = std::find_if(v.begin(), v.end(), IsWeapon());
	if (findItem != v.end())
		cout << "ID: " << findItem->m_itemid << endl;

	/*
	Test();
	Functor func;
	func(10);
	*/

	/*
	Item i1;
	TEST_FUNC fn;
	fn = &Item::test;
	i1.test();
	(i1.*fn)();

	Item* i2 = new Item;
	(i2->*fn)();
	*/
}
