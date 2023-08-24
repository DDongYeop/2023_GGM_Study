#include <iostream>
#include <vector>
#include <queue>

#define MAX_VTXS 256

using namespace std;

static vector<bool> visited;

class AdjMatGraph
{
protected:
	int size = 0;
	vector<char> vertices;
	vector<vector<int>> adj;

public:
	AdjMatGraph()
	{
		vertices.resize(MAX_VTXS);
		adj.resize(MAX_VTXS);
		for (int i = 0; i < MAX_VTXS; ++i)
			adj[i].resize(MAX_VTXS);
		visited.resize(MAX_VTXS, false);
		Reset();
	}

	char GetVertex(int i)
	{
		return vertices[i];
	}

	int GetEdge(int i, int j)
	{
		return adj[i][j];
	}

	void SetEdge(int i, int j, int val)
	{
		adj[i][j] = val;
	}

	bool IsEmpty()
	{
		return size == 0;
	}

	bool IsFull()
	{
		return size >= MAX_VTXS;
	}

	void Reset()
	{
		size = 0;
		for (int i = 0; i < MAX_VTXS; i++)
			for (int j = 0; j < MAX_VTXS; j++)
				SetEdge(i, j, 0);
	}

	void InsertVertex(char ch)
	{
		if (IsFull())
			return;

		vertices[size++] = ch;
	}

	void InsertEdge(int x, int y)
	{
		adj[x][y] = 1;
		adj[y][x] = 1;
	}

	void Display()
	{
		cout << "  ";
		for (int i = 0; i < size; ++i)
			cout << vertices[i] << ' ';

		for (int i = 0; i < size; ++i)
		{
			cout << '\n' << vertices[i] << ' ';

			for (int j = 0; j < size; ++j)
				cout << adj[i][j] << ' ';
		}
	}

	void BFS(int index)
	{
		queue<int> que;
		que.push(index);
		visited[index] = true;

		while (!que.empty())
		{
			int current = que.front();
			cout << current << ' ';
			que.pop();

			for (int i = 0; i < MAX_VTXS; ++i)
			{
				if (visited[i] || adj[current][i] == 0)
					continue;
				visited[i] = true;
				que.push(i);
			}
		}
	}


};

int main()
{
	int n, m, temp1, temp2;
	cout << "정점의 개수와 간선의 수 :";
	cin >> n >> m;
	cout << "간선의 시작정점과 끝 정점 :" << endl;

	AdjMatGraph g;
	for (int i = 0; i < n; i++)
		g.InsertVertex('A' + i);

	for (int i = 0; i < m; i++)
	{
		cin >> temp1 >> temp2;
		g.InsertEdge(temp1, temp2);
	}

	cout << "인접 행렬로 표현한 그래프" << endl;
	g.Display();
	cout << "\BF 탐색 => ";
	g.BFS(0);
	return 0;
}
