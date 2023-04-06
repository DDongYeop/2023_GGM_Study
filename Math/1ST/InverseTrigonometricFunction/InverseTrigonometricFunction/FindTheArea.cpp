#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int main()
{
	vector<int> x, y;
	int a, b;

	cout << "====================\n";
	cout << " 다각형의 넓이 구하기 \n";
	cout << "====================\n\n";
	cout << "몇가지의 꼭지점의 정보를 입력한 후, \n꼭지점의 정보를 입력하세요.\n";

	while (cin >> a >> b)
	{
		if (a == 0 && b == 0)
			break;
		x.push_back(a);
		y.push_back(b);
	}


}
