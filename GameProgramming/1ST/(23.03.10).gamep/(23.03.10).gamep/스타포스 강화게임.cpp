#include <iostream>

using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	cout << "=================" << endl;
	cout << "스타포스 강화 게임" << endl;
	cout << "=================" << endl << endl;
	int iUpgrade = 0;
	float fPercent = 0.f;
	cout << "현재 무기는 몇성인가요?" << endl;
	cin >> iUpgrade;
	switch (iUpgrade)
	{
	case 0:
	case 1:
	case 2:
		fPercent = 90;
		break;
	case 3:
	case 4:
	case 5:
		fPercent = 50;
		break;
	case 6:
	case 7:
	case 8:
	case 9:
		fPercent = 10;
		break;
	default:
		fPercent = 1;
		break;
	}
	cout << "현재 무기 UPgrade : " << iUpgrade << "성" << endl;
	cout << "강화 확률 Percent : " << fPercent << "%" << endl;
	cout << "강화하시겠습니까? 예:1 , 아니오: 0" << endl;
	int iInput;
	cin >> iInput;

	if (iInput == 0) //종료조건 처리.
		return 0;

	if (fPercent > rand() % 101 + 1)
		cout << "강화 성공";
	else
		cout << "강화 실패";
}
