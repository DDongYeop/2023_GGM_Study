#include <iostream>

using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	cout << "=================" << endl;
	cout << "스타포스 강화 게임" << endl;
	cout << "=================" << endl << endl;
	int iUpgrade = 0;
	float fPercent = rand() % 10001 * 0.01f;
	cout << "현재 무기는 몇성인가요?" << endl;
	cin >> iUpgrade;
	cout << "현재 무기 UPgrade : " << iUpgrade << "성" << endl;
	cout << "강화 확률 Percent : " << fPercent << "%" << endl;
	cout << "강화하시겠습니까? 예:1 , 아니오: 0" << endl;
	int iInput;
	cin >> iInput;

	if (iInput == 0) //종료조건 처리.
		return 0;

	if (iUpgrade >= 0 && iUpgrade <= 2)
	{
		if (fPercent <= 90)
			cout << "강화 성공" << endl;
		else
			cout << "강화 실패" << endl;
	}
}
