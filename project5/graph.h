#ifndef GRAPH_H
#define GRAPH_H

#include <QString>
#include <QFile>
#include <QComboBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTextBrowser>

#include <vector>
#include <queue>

//因兼容性问题
//#include <QTextStream>
//#include <QTextCodec>

class Graph
{
public:
    struct City
    {
        QString name;
        double Loc_x;
        double Loc_y;
    };

    struct Edge
    {
        City *BeginCity;
        City *EndCity;
        int weidgt;
    };

    Graph();
    void addPoint(QComboBox *BeginPoint, QComboBox *EndPoint);
    void drawPoint(QGraphicsScene *Scene);
    void PathSearch(QComboBox *BeginPoint, QComboBox *EndPoint, QTextBrowser *Path, QTextBrowser *Long, QGraphicsScene *Scene);


private:
    std::vector<City> Cities;
    std::vector<Edge> Edges;

    int MaxX, MaxY, MinX, MinY;

    void DataInput();
    void MapEdge();
    int FindCityIndex(QString CityName);
    std::vector<int> ShortestPath(int src, int dst, int &outDist);

};

#endif // GRAPH_H
