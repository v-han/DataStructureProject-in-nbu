#include "linklist.h"


// 节点的构造函数
LNode::LNode() {
    this->next = nullptr;
    this->val = new StuInfo();
}


LNode::~LNode(){
    delete val;
}


LNode::LNode(const string &n,const string &b):next(nullptr){
    StuInfo* stu = new StuInfo();
    stu->setBirth(b);
    stu->setName(n);
    this->val = stu;
}




// 链表的构造函数

LinkList::LinkList(){
    this->head = new LNode();
    this->length = 0;
}


LinkList::~LinkList(){
    while(head != nullptr){
        LNode *temp = head;
        head = head->next;
        delete temp;
    }
}


string LinkList::showLinkList(){
    // TODO: 展示链表
    LNode *p = head->next;
    string str = "";
    while(p){
        str += "name:"+p->val->getName()+" birth:"+p->val->getBirth()+"     ";
        p = p->next;
    }
    return str;
}


bool LinkList::addNode(const string& n,const string &b,int index){
    // TODO: 添加节点
    LNode *p = head;
    //LNode *q;
    LNode *tmp;
    int cnt = 1;
    if (index > length+1 or index < 1){
        return false;
    }

    while (p->next and cnt < index){
        //q = p;
        p = p->next;
        cnt++;
    }

    tmp = new LNode(n,b);
    // if (index == 1){
    //     tmp->next = head->next;
    //     head->next = tmp;
    // }
    // else{
    //     tmp->next = q->next;
    //     q->next = tmp;
    // }
    tmp->next = p->next;
    p->next = tmp;

    length++;
    return true;
}

bool LinkList::deleteNode(int index){
    // TODO: 删除节点
    LNode *p = head;
    LNode *tmp;
    int cnt = 1;

    if (index > length or index < 1){
        return false;
    }

    while (p->next and cnt < index){
        p = p->next;
        cnt++;
    }

    // if (index == 1){
    //     tmp = head;
    //     head = head->next;
    //     delete tmp;
    // }
    // else{
    //     tmp = p->next;
    //     p->next = p->next->next;
    //     delete tmp;
    // }
    tmp = p->next;
    p->next = tmp->next;
    delete tmp;

    length--;
    return true;
}


LNode* LinkList::findNode(const string &n){
    // TODO: 查找节点
    LNode *p = head->next;
    while (p){
        if (p->val->getName() == n)
            return p;
        p = p->next;
    }
    return nullptr;
}

void LinkList::clearList(){
    // TODO:清空链表
    while(head != nullptr){
        LNode *temp = head;
        head = head->next;
        delete temp;
    }
    head = new LNode();
    length = 0;
}
