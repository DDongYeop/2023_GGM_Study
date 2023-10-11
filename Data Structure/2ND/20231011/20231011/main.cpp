#include "bt.h"

int main() 
{
    BTreeNode* bt1 = MakeBTreeNode();
    BTreeNode* bt2 = MakeBTreeNode();
    BTreeNode* bt3 = MakeBTreeNode();
    BTreeNode* bt4 = MakeBTreeNode();
    BTreeNode* bt5 = MakeBTreeNode();

    BST bst;
    SetData(bt1, 1);
    SetData(bt2, 2);
    SetData(bt3, 3);
    SetData(bt4, 4);
    SetData(bt5, 5);
    bst.Insert(bt3);
    bst.Insert(bt2);
    bst.Insert(bt1);
    bst.Insert(bt4);
    bst.Insert(bt5);
    bst.Delete(2);
    bst.Print(bst.root, 10, 0);

}
