#include <iostream>
#include <thread>
#include <ctime>

using namespace std;

void Add(int* val, int min, int max);

int main()
{
	// Thread를 사용하면 같은 값은 같이 접근하기에 값이 올바르지 않을 수도 있다. 

#pragma region Thread

	int num = 0; 
	clock_t start = clock();
	thread t1(Add, &num, 1, 3333);
	thread t2(Add, &num, 3334, 6666);
	thread t3(Add, &num, 6667, 10000);
	
	t1.join();
	t2.join();
	t3.join();

	clock_t end = clock();
	cout << num << '\n';
	cout << (end - start) << "\n\n";

#pragma endregion

#pragma region Normal

	num = 0; 
	start = clock();
	Add(&num, 1, 10000);
	end = clock();
	cout << num << '\n';
	cout << (end - start) << '\n';

#pragma endregion
}

void Add(int* val, int min, int max)
{
	for (int i = min; i <= max; ++i)
	{
		*val += i;
	}
}
