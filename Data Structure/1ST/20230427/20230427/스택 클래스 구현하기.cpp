#include <iostream>
using namespace std;

class Stack
{
private:
	const static int SIZE = 10;
	char name;
	char chArray[SIZE];
	int topIndex;

public:
	Stack(char ch = ' ') : name{ch}, topIndex{-1}
	{
		cout << "Constructing stack " << name << '\n';
	}

	void push(char ch)
	{
		if (topIndex == SIZE - 1)
		{
			cout << "Stack " << name << " is full\n";
			return;
		}
		chArray[++topIndex] = ch;
	}

	char pop()
	{
		if (topIndex == -1)
		{
			cout << "Stack " << name << " is empty\n";
			return ' ';
		}
		
		return chArray[topIndex--];
	}
};

int main()
{
	Stack s1{ 'A' }, s2{ 'B' };
	s1.push('d');
	s1.push('a');
	s1.push('t');
	s1.push('a');

	s2.push('s');
	s2.push('t');
	s2.push('a');
	s2.push('c');
	s2.push('k');

	for (int i = 0; i < 5; ++i)
		cout << "Pop s1: " << s1.pop() << "\n";
	cout << '\n';
	for (int i = 0; i < 5; ++i)
		cout << "Pop s2: " << s2.pop() << '\n';
	
	return 0;
}
