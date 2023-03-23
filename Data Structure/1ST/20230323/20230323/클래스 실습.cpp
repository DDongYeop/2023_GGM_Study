#include <iostream>
using namespace std;

class Pizza
{
public:
	int size = 0;
	Pizza(int size) : size{ size } {};
};

void MakeDouble(Pizza &pizza)
{
	pizza.size *= 2;
}

int main()
{
	Pizza pizza(10);
	MakeDouble(pizza);
	cout << pizza.size << "ÀÎÄ¡ ÇÍÂ¥\n";
}
