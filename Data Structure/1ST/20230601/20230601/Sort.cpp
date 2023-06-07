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
	int temp; //swap�� ���� ����
	int lessIndex; //���� ���� �ε����� ������ ���� ����

	for (int i = 0; i < vec.size(); ++i) 
	{
		lessIndex = i; //���� �� ���� ���� ���� ���� ������ ����
		for (int j = i; j < vec.size(); ++j) 
			if (vec[lessIndex] > vec[j]) //lessIndex���� j�� �� ���� �ִ� ���� �� �۴ٸ� 
				lessIndex = j; //lessIndex�� j�� 

		//�Ʒ��� ���� �Լ�
		temp = vec[lessIndex];
		vec[lessIndex] = vec[i];
		vec[i] = temp;
	}

	PrintVector(vec);
}

void InsertionSort(vector<int> vec)
{
	int i, j, temp;

	for (i = 1; i < vec.size(); ++i) //ù���� ���� Ȯ�� �� ���� ���� �� ��ġ �״���̱⿡ �پ�Ѱ� ����
	{
		temp = vec[i]; 
		for (j = i - 1; j >= 0; --j) //temp�� �־�� i������ 1 ���� ������ �����Ͽ� 0���� 
		{
			if (vec[j] > temp) //i�ε����� ���� j�ε����� ���ٺ��� �۴ٸ� 
				vec[j + 1] = vec[j]; //j���� ������ �о��� 
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


// ��������(Selection Sort)
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
// https://www.youtube.com/watch?v=7OShOicP0pE
