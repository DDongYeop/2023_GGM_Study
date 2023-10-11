#include "bt.h"

BTreeNode* MakeBTreeNode(void)
{
	//make binary tree
	//initialize
	//return pointer

	BTreeNode* nd = new BTreeNode;
	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

BTreeNode* GetLeftSubTree(BTreeNode* nd)
{
	return nd->left;
}

BTreeNode* GetRightSubTree(BTreeNode* nd)
{
	return nd->right;
}

void DeleteBTreeNode(BTreeNode* bt) {
	delete bt;
}
int GetData(BTreeNode* bt) {
	return bt->data;
}
void SetData(BTreeNode* bt, int data) {
	bt->data = data;
}

void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub) {
	// if there is a node in left link, delete it
	// put sub in left link of main

	if (main->left != NULL) {
		delete main->left;
	}
	main->left = sub;
}
void MakeRightSubTree(BTreeNode* main, BTreeNode* sub) {
	// if there is a node in right link, delete it
	// put sub in right link of main

	if (main->right != NULL) {
		delete main->left;
	}
	main->right = sub;
}
void PreorderTraverse(BTreeNode* bt)
{
	// 구현해보자!
	if (bt == NULL) return;
	cout << bt->data;
	PreorderTraverse(bt->left);
	PreorderTraverse(bt->right);
	return;
}
void InorderTraverse(BTreeNode* bt)
{
	// 구현해보자!
	if (bt == NULL) return;
	InorderTraverse(bt->left);
	cout << bt->data;
	InorderTraverse(bt->right);
	return;
}
void PostorderTraverse(BTreeNode* bt)
{
	// 구현해보자!
	if (bt == NULL) return;
	PostorderTraverse(bt->left);
	PostorderTraverse(bt->right);
	cout << bt->data;
	return;
}


