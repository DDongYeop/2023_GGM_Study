#include <iostream>
#include <vector>
using namespace std;

int main()
{

#pragma region 2번 문제

	string str = "I love c++";
	cout << str << endl;
	int pos = str.find("++");// (1) 
	cout << "++이 시작되는 인덱스는 : " << pos << endl; // 8 
	cout << str.erase(pos) << endl; // I love c
	cout << str.insert(pos, "#") << endl; // I love c#
	

#pragma endregion


#pragma region 3번 문제

	vector<int> v1{ 1,3,4,5,6 };
	// Number1
	v1.push_back(7);
	// Number2
	v1.pop_back();
	// Number3
	cout << v1.front() << '\n';
	// Number4
	cout << v1.back() << '\n';
	// Number5
	cout << v1.size() << '\n';
	// Number6
	v1.insert(v1.begin()+1, 2);
	// Number7
	v1.erase(v1.begin() + 1, v1.begin() + 3);

#pragma endregion
	return 0;
}
