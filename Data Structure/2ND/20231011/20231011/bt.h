#pragma once
#include <iostream>
#include<stack>
using namespace std;

struct BTreeNode
{
	int data;
	struct BTreeNode* left;
	struct BTreeNode* right;
};

BTreeNode* MakeBTreeNode(void);
void DeleteBTreeNode(BTreeNode* bt);
int GetData(BTreeNode* bt);
void SetData(BTreeNode* bt, int data);
void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub);
void MakeRightSubTree(BTreeNode* main, BTreeNode* sub);
BTreeNode* GetLeftSubTree(BTreeNode* nd);
BTreeNode* GetRightSubTree(BTreeNode* nd);
void PreorderTraverse(BTreeNode* bt);
void InorderTraverse(BTreeNode* bt);
void PostorderTraverse(BTreeNode* bt);


class BST {
public:
	BTreeNode* root = NULL;
	void Insert(BTreeNode* node);
	void InsertRecur(BTreeNode* root, BTreeNode* node);
	void Delete(int key);
	void Delete(BTreeNode* parent, BTreeNode* node);
	void SetCursorPosition(int x, int y);
	void Print(BTreeNode* node, int x, int y);
};