#include <iostream>
using namespace std;

class Character
{
public:
	int x, y, hp;
	Character(int x, int y, int hp)
	{
		this->x = x;
		this->y = y;
		this->hp = hp;
	}

	void SetX(int x)
	{
		this->x = x;
	}

	void Print()
	{
		cout << "x : " << x << "\ty : " << y << "\tHP : " << hp << '\n';
	}
};

int main()
{
	cout << "Ä³¸¯ÅÍ #1\n";
	Character cha(0, 0, 100);
	for (int i = 0; i < 100; i += 10)
	{
		cha.SetX(i);
		cha.Print();
	}
}