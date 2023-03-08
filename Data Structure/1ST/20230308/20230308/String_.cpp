#include <iostream>

using namespace std;

int main()
{
	char str1[] = { 'h', 'e', 'l', 'l', 'o', NULL }; // 그냥 얘를 출력하면 儆 이런 문자가 뜨곤 한다 
													 // 근데 뒤에 NULL값 즉 쓰레기 값을 넣어주어야한다 
	cout << str1;
}