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
1) c++���� struct�� class�� ���̴�? => ���� ������
2) Ŭ������ Ʋ�� ���̴�. 
3) Ŭ���� ���� �Լ��� �����ϸ� inline Ű���尡 �ٴ´�. �� inline �Լ�: �������� �� �� �Լ��� ȣ��Ǵ� ��ġ�� �ڵ带 �����Ѵ�. 
5) ������(N), �Ҹ���(1)
=> �⺻������, ��������� ���
4) �Ϲ��Լ��� ����Լ��� ��������?
6) ��ü������ 3�� Ư¡
1 ���(�θ� -> �ڽ�): ������ ȣ��(�θ�-> �ڽ�), �Ҹ��� ȣ��(�ڽ� -> �θ�)
2 ĸ��ȭ: public, protected, private => Get Set
3 ������: �����ε�(�Լ� �ߺ� ����), �������̵�(������), virtual
7) �߻�Ŭ������ ������� ���������Լ��� �����ؾ�


*/