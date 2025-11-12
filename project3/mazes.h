#ifndef MAZES_H
#define MAZES_H

class Mazes
{
public:
    Mazes();
    char GetInfo(int posI,int posJ);
    void SetInfo(int posI,int posJ,char input);
    void Reset();

private:
    char Array[9][9];
};

#endif // MAZES_H
