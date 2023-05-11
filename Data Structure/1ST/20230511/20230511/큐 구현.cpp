#include <iostream>
using namespace std;

class Queue
{
	int* but;
	int qsize;
	int front;
	int rear;

public:
	void InitQueue(int qsize)
	{
		but = new int[qsize];
		this->qsize = qsize;
		front = rear = -1;
	}

	void Enqueue(int data)
	{
		if (qsize == rear + 1)
		{
			cout << "Å¥°¡ ²Ë Ã¡À½\n";
			return;
		}

		++rear;
		but[rear] = data;
	}

	int Dequeue()
	{
		if (front == rear)
		{
			cout << "Å¥°¡ ºñ¾îÀÖÀ½\n";
			return -1;
		}
		++front;
		return but[front];
	}

	int IsFull()
	{
		if (rear == qsize)
			return 1;
		return 0;
	}

	int IsEmpty()
	{
		if (rear == front)
			return 1;
		return 0;
	}
};

int main()
{
	int i;
	Queue q1;
	q1.InitQueue(10);
	for (int i = 1; i <= 11; ++i)
	{
		cout << i << " ÀÔ·Â \n";
		q1.Enqueue(i);
	}
	cout << '\n';

	while (!q1.IsEmpty())
	{
		cout << q1.Dequeue() << " Ãú·Â \n";
	}
	cout << '\n';
	return 0;
}
