#include "bt.h"

BTreeNode* MakeBTreeNode(void)
{
	//make binary tree
	BTreeNode* nd = new BTreeNode;
	//initialize
	nd->left = NULL;
	nd->right = NULL;
	//return pointer
	return nd;

}

void DeleteBTreeNode(BTreeNode* bt) 
{
	delete bt;
}

int GetData(BTreeNode* bt) 
{
	return bt->data;
}

void SetData(BTreeNode* bt, int data) 
{
	bt->data = data;
}

void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub) 
{
	// if there is a node in left link, delete it
	if (main->left != NULL)
		delete main->left;
	// put sub in left link of main
	main->left = sub;

}

void MakeRightSubTree(BTreeNode* main, BTreeNode* sub) 
{
	// if there is a node in right link, delete it
	if (main->right != NULL)
		delete main->right;
	// put sub in right link of main
	main->right = sub;

}

void PreorderTraverse(BTreeNode* bt)
{
	// 종료조건
	if (bt == NULL)
		return;
	// 구현해보자!
	cout << bt->data;
	PreorderTraverse(bt->left);
	PreorderTraverse(bt->right);
}

void InorderTraverse(BTreeNode* bt)
{
	// 종료조건
	if (bt == NULL)
		return;
	// 구현해보자!
	InorderTraverse(bt->left);
	cout << bt->data;
	InorderTraverse(bt->right);
}

void PostorderTraverse(BTreeNode* bt)
{
	if (bt == NULL)
		return;
	// 구현해보자!
	PostorderTraverse(bt->left);
	PostorderTraverse(bt->right);
	cout << bt->data;
}
