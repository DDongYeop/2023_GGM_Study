#include <iostream>
#include <unordered_set>

using namespace std;

int main()
{
	unordered_set<int> s1;

	int loop, input;
	cin >> loop;

	while (loop--)
	{
		cin >> input;
		s1.insert(input);
	}

	cin >> loop;
	while (loop--)
	{
		cin >> input;
		if (s1.find(input) == s1.end())
			cout << "0 ";
		else 
			cout << "1 ";
	}
}
