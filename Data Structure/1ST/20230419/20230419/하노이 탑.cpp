#include <iostream>
using namespace std;

void HanoiTower(int num, char from, char by, char to);

int main()
{
	HanoiTower(2, 'A', 'B', 'C');
}

void HanoiTower(int num, char from, char by, char to) 
{
	if (num == 1)
	{
		cout << "원반1을 " << from << "에서 " << to << "로 이동" << endl;

	}
	else
	{
		HanoiTower(num - 1, from, to, by);
		cout << "원반" << num << "을(를)" << from << "에서" << to << "로 이동" << endl;
		HanoiTower(num - 1, by, from, to);
	}
}