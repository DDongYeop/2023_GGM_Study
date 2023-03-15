#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> v;
	for (int i = 0; i < 1000; i++)
	{
		v.push_back(100);
		cout << v.size() << " " << v.capacity() << endl;
	}
}