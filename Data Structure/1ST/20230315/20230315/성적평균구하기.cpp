#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> vec;
	int index;
	while (1)
	{
		cout << "성적을 입력하세요. (종료는 -1) : ";
		cin >> index;
		if (index == -1)
			break;
		vec.push_back(index);
	}
	index = 0;
	for (int i = 0; i < vec.size(); i++)
		index += vec[i];
	cout << "성적 평균 : " << index / vec.size();
}