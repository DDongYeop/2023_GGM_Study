#include <iostream>
using namespace std;

int main()
{
	int age;
	while (true)
	{
		try
		{
			cout << "���̸� �Է��ϼ��� !! \n";
			cin >> age;
			if (age < 0)
				throw age;
			else if (age >= 120)
				throw 'c';
			else if (25 <= age)
				throw 1.1f;
			cout << age << "���� û�ҳ��Թ̴� !!";
			break;
		}
		catch (int age)
		{
			cout << "����� �Է��ϼ���\n";
			continue;
		}
		catch (float f)
		{
			cout << "û�ҳ��� �ƴմϴ�\n";
			continue;
		}
		catch (char ch)
		{
			cout << "�ٽ��Է��ϼ���\n";
			continue;
		}
	}
}