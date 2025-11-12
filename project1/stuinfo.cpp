#include "stuinfo.h"
using namespace std;


StuInfo::StuInfo(){

}


StuInfo::StuInfo(const string &n,const string &b):name(n),birth(b){
    //this->setBirth(b);
    //this->setName(n);
}


StuInfo::~StuInfo(){

}

void StuInfo::setName(const string &n){
    name = n;
}

void StuInfo::setBirth(const string &b){
    birth = b;
}

string StuInfo::getBirth()const{
    return birth;
}

string StuInfo::getName()const{
    return name;
}
