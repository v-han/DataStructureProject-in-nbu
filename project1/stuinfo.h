#ifndef STUINFO_H
#define STUINFO_H

#endif // STUINFO_H
#include <string>
using namespace std;

class StuInfo{
private:
    string name;
    string birth;
public:
    // 无参构造
    StuInfo();
    // 带参构造
    StuInfo(const string &n,const string &b);
    // 析构
    ~StuInfo();

    string getName() const;
    string getBirth() const;

    void setName(const string &n);
    void setBirth(const string &b);

};


