#ifndef LINKLIST_H
#define LINKLIST_H
#include "stuinfo.h"

class LNode
{
public:
    StuInfo* val;
    LNode* next;
    LNode();
    LNode(const string &n,const string &b);
    ~LNode();
};



class LinkList
{
public:
    LNode* head;
    int length;
    LinkList();
    ~LinkList();
    bool addNode(const string& n,const string& b,int index); //添加节点
    bool deleteNode(int index); // 删除节点
    LNode* findNode(const string &n); // 查询节点
    string showLinkList(); // 展示链表
    void clearList(); // 清空链表
};

#endif // LINKLIST_H
