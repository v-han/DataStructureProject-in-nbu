#include "binarytree.h"

BinaryTree::BinaryTree() :RootNode(nullptr){}

TreeNode* BinaryTree::rightRotate(TreeNode *y)
{
    TreeNode *x = y->LNode;
    TreeNode *T2 = x->RNode;

    x->RNode = y;
    y->LNode = T2;

    y->height = std::max(getHeight(y->LNode), getHeight(y->RNode)) + 1;
    x->height = std::max(getHeight(x->LNode), getHeight(x->RNode)) + 1;

    return x;
}

TreeNode* BinaryTree::leftRotate(TreeNode *x)
{
    TreeNode *y = x->RNode;
    TreeNode *T2 = y->LNode;

    y->LNode = x;
    x->RNode = T2;

    x->height = std::max(getHeight(x->LNode), getHeight(x->RNode)) + 1;
    y->height = std::max(getHeight(y->LNode), getHeight(y->RNode)) + 1;

    return y;
}

TreeNode* BinaryTree::insert(TreeNode *Treeptr, int num) {
    if (!Treeptr)
        return new TreeNode(num);

    if (num < Treeptr->num)
        Treeptr->LNode = insert(Treeptr->LNode, num);
    else if (num > Treeptr->num)
        Treeptr->RNode = insert(Treeptr->RNode, num);
    else
        return Treeptr; // 不允许重复

    //增加树的高度
    Treeptr->height = 1 + std::max(getHeight(Treeptr->LNode), getHeight(Treeptr->RNode));

    int balance = getBalanceFact(Treeptr);

    // LL型
    if (balance > 1 && num < Treeptr->LNode->num)
        return rightRotate(Treeptr);
    // RR型
    if (balance < -1 && num > Treeptr->RNode->num)
        return leftRotate(Treeptr);
    // LR型
    if (balance > 1 && num > Treeptr->LNode->num) {
        Treeptr->LNode = leftRotate(Treeptr->LNode);
        return rightRotate(Treeptr);
    }
    // RL型
    if (balance < -1 && num < Treeptr->RNode->num) {
        Treeptr->RNode = rightRotate(Treeptr->RNode);
        return leftRotate(Treeptr);
    }

    return Treeptr;
}

void BinaryTree::TreeInsert(int num)
{
    RootNode = insert(RootNode,num);
}

void BinaryTree::destroy(TreeNode *Treeptr)
{
    if (!Treeptr) return;
    destroy(Treeptr->LNode);
    destroy(Treeptr->RNode);
    delete Treeptr;
}

void BinaryTree::TreeClear()
{
    destroy(RootNode);
    RootNode = nullptr;
}

QString BinaryTree::inorderPrint(TreeNode *Treeptr)
{
    if (Treeptr == nullptr)
        return "";
    QString str = "";
    //访问左子树
    str += inorderPrint(Treeptr->LNode);
    //访问根节点
    str += QString::number(Treeptr->num) + ",";
    //访问右子树
    str += inorderPrint(Treeptr->RNode);

    return str;
}

QString BinaryTree::inorderPrintOut()
{
    return inorderPrint(RootNode);
}

int BinaryTree::getTotalHeight()
{
    return getHeight(RootNode);
}

TreeNode* BinaryTree::getRootNode() const
{
    return RootNode;
}

TreeNode* BinaryTree::deleteNode(TreeNode* Treeptr, int num)
{
    if (!Treeptr) return Treeptr;

    //普通 BST 删除逻辑
    if (num < Treeptr->num)
        Treeptr->LNode = deleteNode(Treeptr->LNode, num);
    else if (num > Treeptr->num)
        Treeptr->RNode = deleteNode(Treeptr->RNode, num);
    else
    {
        // 找到要删除的节点
        if (!Treeptr->LNode || !Treeptr->RNode)
        {
            TreeNode *temp = Treeptr->LNode ? Treeptr->LNode : Treeptr->RNode;
            if (!temp)
            {
                temp = Treeptr;
                Treeptr = nullptr;
            }
            else
            {
                *Treeptr = *temp; // 用子节点内容替换当前节点
            }
            delete temp;
        }
        else
        {
            // 有两个子节点：找右子树最小节点
            TreeNode* minNode = Treeptr->RNode;
            while (minNode->LNode)
                minNode = minNode->LNode;

            Treeptr->num = minNode->num;
            Treeptr->RNode = deleteNode(Treeptr->RNode, minNode->num);
        }
    }

    if (!Treeptr)
        return Treeptr; // 删除后为空

    //更新高度
    Treeptr->height = 1 + std::max(getHeight(Treeptr->LNode), getHeight(Treeptr->RNode));

    //检查平衡并旋转
    int balance = getBalanceFact(Treeptr);

    //LL型
    if (balance > 1 && getBalanceFact(Treeptr->LNode) >= 0)
        return rightRotate(Treeptr);

    //LR型
    if (balance > 1 && getBalanceFact(Treeptr->LNode) < 0)
    {
        Treeptr->LNode = leftRotate(Treeptr->LNode);
        return rightRotate(Treeptr);
    }

    //RR型
    if (balance < -1 && getBalanceFact(Treeptr->RNode) <= 0)
        return leftRotate(Treeptr);

    //RL型
    if (balance < -1 && getBalanceFact(Treeptr->RNode) > 0)
    {
        Treeptr->RNode = rightRotate(Treeptr->RNode);
        return leftRotate(Treeptr);
    }

    return Treeptr;
}

void BinaryTree::TreeDelete(int num)
{
    RootNode = deleteNode(RootNode, num);
}
