#include <iostream>

using namespace std;

struct Node
{
	int value = NULL;
	Node* left = NULL;
	Node* right = NULL;
};

void Insert(int index, Node* Parent);
void PostorderTraversal(Node& findNode);

int main()
{
	Node rootNode;
	rootNode.value = NULL;
	int input;
	
	while (cin >> input)
	{
		if (rootNode.value == NULL)
			rootNode.value = input;
		else
			Insert(input, &rootNode);
	}
	PostorderTraversal(rootNode);
}

void Insert(int index, Node* parent)
{
	if (parent->value < index)
	{
		if (parent->right == NULL)
		{
			parent->right = new Node;
			parent->right->value = index;
		}
		else
			Insert(index, parent->right);
	}
	else
	{
		if (parent->left == NULL)
		{
			parent->left = new Node;
			parent->left->value = index;
		}
		else
			Insert(index, parent->left);
	}
}

void PostorderTraversal(Node& findNode)
{
	if (findNode.left != NULL)
		PostorderTraversal(*findNode.left);
	if (findNode.right != NULL)
		PostorderTraversal(*findNode.right);
	cout << findNode.value << '\n';
}
