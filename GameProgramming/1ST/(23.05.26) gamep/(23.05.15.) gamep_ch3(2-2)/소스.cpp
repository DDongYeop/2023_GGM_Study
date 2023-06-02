#include<iostream>
using namespace std;

class Something 
{
private:
	int m_i;
public:
	Something() : m_i(1)
	{
	}
	void print() {
		cout << m_i;
	}
};
int main() {
	Something som;
	som.print();
}

/*
1) c++에서 struct와 class의 차이는? => 접근 지정자
2) 클래스는 틀일 뿐이다. 
3) 클래스 내에 함수를 정의하면 inline 키워드가 붙는다. ※ inline 함수: 컴파일할 때 이 함수가 호출되는 위치에 코드를 복붙한다. 
5) 생성자(N), 소멸자(1)
=> 기본생성자, 복사생성자 등등
4) 일반함수와 멤버함수의 차이점은?
6) 객체지향의 3대 특징
1 상속(부모 -> 자식): 생성자 호출(부모-> 자식), 소멸자 호출(자식 -> 부모)
2 캡슐화: public, protected, private => Get Set
3 다형성: 오버로딩(함수 중복 정의), 오버라이딩(재정의), virtual
7) 추상클래스를 만들려면 순수가상함수를 포함해야


*/