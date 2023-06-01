#include <iostream>
#include <vector>
using namespace std;

void SelectionSort(vector<int> vec);
void InsertionSort(vector<int> vec);
void PrintVector(vector<int> vec);

int main()
{
	vector<int> vec;
	for (int i = 10; i > 0; --i)
		vec.push_back(i);
	
	SelectionSort(vec);
	InsertionSort(vec);
}

void SelectionSort(vector<int> vec)
{
	int temp;
	int lessIndex;

	for (int i = 0; i < vec.size(); ++i)
	{
		lessIndex = i;
		for (int j = i; j < vec.size(); ++j)
			if (vec[lessIndex] > vec[j])
				lessIndex = j;

		temp = vec[lessIndex];
		vec[lessIndex] = vec[i];
		vec[i] = temp;
	}

	PrintVector(vec);
}

void InsertionSort(vector<int> vec)
{
	int i, j, temp;

	for (i = 1; i < vec.size(); ++i)
	{
		temp = vec[i];
		for (j = i - 1; j >= 0; --j)
		{
			if (vec[j] > temp) vec[j + 1] = vec[j];
			else break;
		}
		vec[j + 1] = temp;
	}

	PrintVector(vec);
}

void PrintVector(vector<int> vec)
{
	cout << '\n';
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << ' ';
}


K// 선택정렬(Selection Sort)
// - 정렬이 안 된 요소 중 가장 작은 값을 앞에 두면 알아서 정렬하는 알고리즘
// - 해당 자리를 선택하고 그 자리에 오는 값을 찾는 것
// - 정렬이 완벽하게 된 상태에서도 무조건 다 돈다.
// - (고정)시간 복잡도 O(N ^ 2)
// - 공간 복잡도 O(N)
// 
// 삽입정렬(Insertion Sort)
// - 정렬이 안 된 요소를 정렬된 배열 안의 적절한 위치에 배치하는 알고리즘
// - 2번째 원소부터 시작하여 앞 원소와 비교하여 삽입할 위치를 지정한 후, 원소를 뒤로 옮기고 지정된 위치에 삽입
// - 시간 복잡도 O(N), (최악의 경우) 시간 복잡도 O(N ^ 2)
// - 공간 복잡도 O(N)
//
//
// https://www.youtube.com/watch?v=7OShOicP0pE
