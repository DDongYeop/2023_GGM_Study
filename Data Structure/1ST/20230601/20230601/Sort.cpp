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


K// ��������(Selection Sort)
// - ������ �� �� ��� �� ���� ���� ���� �տ� �θ� �˾Ƽ� �����ϴ� �˰���
// - �ش� �ڸ��� �����ϰ� �� �ڸ��� ���� ���� ã�� ��
// - ������ �Ϻ��ϰ� �� ���¿����� ������ �� ����.
// - (����)�ð� ���⵵ O(N ^ 2)
// - ���� ���⵵ O(N)
// 
// ��������(Insertion Sort)
// - ������ �� �� ��Ҹ� ���ĵ� �迭 ���� ������ ��ġ�� ��ġ�ϴ� �˰���
// - 2��° ���Һ��� �����Ͽ� �� ���ҿ� ���Ͽ� ������ ��ġ�� ������ ��, ���Ҹ� �ڷ� �ű�� ������ ��ġ�� ����
// - �ð� ���⵵ O(N), (�־��� ���) �ð� ���⵵ O(N ^ 2)
// - ���� ���⵵ O(N)
//
//
// https://www.youtube.com/watch?v=7OShOicP0pE
