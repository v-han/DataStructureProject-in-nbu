#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <algorithm>
#include <QString>

struct TreeNode
{
    int num;
    int height;
    TreeNode *LNode;
    TreeNode *RNode;

    TreeNode(int Num):num(Num),height(1),LNode(nullptr),RNode(nullptr){};
    int getNum(){return num;}
};

class BinaryTree
{
public:
    BinaryTree();

    void TreeInsert(int num);
    void TreeClear();
    void TreeDelete(int num);
    QString inorderPrintOut();
    int getTotalHeight();
    TreeNode* getRootNode() const;

private:
    TreeNode *RootNode;

    //内部调用方法
    int getHeight(TreeNode *Node){return Node ? Node->height : 0;}
    int getBalanceFact(TreeNode *Node){return Node ? getHeight(Node->LNode) - getHeight(Node->RNode) : 0;}

    //右旋
    TreeNode* rightRotate(TreeNode *y);
    //左旋
    TreeNode* leftRotate(TreeNode *x);

    TreeNode* insert(TreeNode *Treeptr,int num);
    TreeNode* deleteNode(TreeNode* Treeptr, int num);
    void destroy(TreeNode *Treeptr);
    QString inorderPrint(TreeNode *Treeptr);

};

#endif // BINARYTREE_H
