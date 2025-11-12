#include "mazes.h"

Mazes::Mazes()
{
    //i表示的是入口
    //o表示的是出口
    //e表示的是空
    //q表示的是墙
    //d表示的是走过
    for (int i = 0;i < 9;i++)
    {
        for (int j = 0;j < 9;j++)
            Array[i][j] = 'e';
    }

    Array[0][0] = 'i';
    Array[8][8] = 'o';  //o表示的是出口
}

char Mazes::GetInfo(int posI,int posJ)
{
    return Array[posI][posJ];
}

void Mazes::SetInfo(int posI,int posJ,char input)
{
    Array[posI][posJ] = input;
}

void Mazes::Reset()
{
    for (int i = 0;i < 9;i++)
    {
        for (int j = 0;j < 9;j++)
        {
            if (Array[i][j] == 'd')
                Array[i][j] = 'e';
        }
    }

    Array[0][0] = 'i';
    Array[8][8] = 'o';
}
