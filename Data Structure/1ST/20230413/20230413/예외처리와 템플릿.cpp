#include <iostream>
using namespace std;

int main()
{
	int pizza_slices = 0;
	int persons = -1;
	int slices_per_person = 0;
	cout << "피자 조각수를 입력하시오: ";
	cin >> pizza_slices;
	while (true)
	{
		try
		{
			cout << "사람수를 입력하시오(1이상): ";
			cin >> persons;
			if (persons <= 0)
				throw persons;
			slices_per_person = pizza_slices / persons;
			cout << "한사람당 피자는 " << slices_per_person << "입니다." << endl;
			break;
		}
		catch (int e)
		{
			cout << "사람수가 " << e << " 0이하입니다.\n";
			continue;
		}
	}
}
