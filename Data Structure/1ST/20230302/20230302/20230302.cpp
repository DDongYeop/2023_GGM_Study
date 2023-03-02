#include <iostream> // iostream이라는 라이브러리를 추가한다 
					// cin, cout을 사용 
					// # << 전처리 지시자 
#include <string>

using namespace std; // std이라는 네임스페이스를 사용한다 
					 // 영역 설정 만약 이게 없다면 std::cin이런식으로 써줘야한다 

int main() // 프로그램 시작시 같이 시작 
		   // return 안 해주면 해줬다고 생각하고 한다 자동처리 
{
#pragma region 입출력 
	
	char arr[100];
	cout << "What's tour name?" << endl; // 출력 << 저쪽으로 
										 // endl 줄바꿈, \n이랑 똑같다 
	cin >> arr;
	cout << "hi" << " " << arr; // 입력 >> 저쪽으로 

#pragma endregion

#pragma region Hello World!

	cout << "Hello World!";

#pragma endregion

#pragma region 사칙연산

	int a, b;
	cin >> a >> b;
	cout << a + b << endl;
	cout << a - b << endl;
	cout << a * b << endl;
	cout << a / b << endl;
	cout << a % b << endl;

#pragma endregion

#pragma region ??!

	string str;
	cin >> str;
	cout << str << "??!";

#pragma endregion




}
