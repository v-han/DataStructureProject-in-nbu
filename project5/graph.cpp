#include "graph.h"

Graph::Graph()
{
    DataInput();
}

//数据输入
void Graph::DataInput()
{
    //读入城市数据
    QFile FileCity(":/new/prefix1/src/cities.csv");
    if (FileCity.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&FileCity);
        //Qt6 方式
        in.setEncoding(QStringConverter::Utf8);
        //Qt5以下 方式
        //in.setCodec("UTF-8");

        while (!in.atEnd())
        {
            QString line = in.readLine().trimmed();

            if (line.isEmpty())
                continue;

            auto parts = line.split(",");

            if (parts.size() >= 1) {
                City city;
                city.name = parts[1];
                city.Loc_x = parts[2].toDouble();
                city.Loc_y = parts[3].toDouble();
                Cities.push_back(city);
            }
        }

        FileCity.close();
    }

    //读入边的数据
    QFile FileEdge(":/new/prefix1/src/edges.csv");
    if (FileEdge.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&FileEdge);
        //Qt6 方式
        in.setEncoding(QStringConverter::Utf8);
        //Qt5以下 方式
        //in.setCodec("UTF-8");


        while (!in.atEnd())
        {
            QString line = in.readLine().trimmed();

            if (line.isEmpty())
                continue;

            auto parts = line.split(",");

            if (parts.size() >= 1) {
                Edge edge;
                edge.BeginCity = &Cities[parts[0].toInt()];
                edge.EndCity = &Cities[parts[1].toInt()];
                edge.weidgt = parts[2].toInt();
                Edges.push_back(edge);
            }
        }

        FileCity.close();
    }
}

//为ComboBox加入元素
void Graph::addPoint(QComboBox *BeginPoint,QComboBox *EndPoint)
{
    int length = Cities.size();
    QString PointName;
    for (int i = 0;i < length;i++)
    {
        PointName = Cities[i].name;
        BeginPoint->addItem(PointName);
        EndPoint->addItem(PointName);
    }
}

//找到图的范围
void Graph::MapEdge()
{
    MaxX = 0, MaxY = 0;
    MinX = 200, MinY = 200;
    int length = Cities.size();
    for (int i = 0;i < length;i++)
    {
        MaxX = (MaxX > Cities[i].Loc_x) ? MaxX : Cities[i].Loc_x;
        MaxY = (MaxY > Cities[i].Loc_y) ? MaxY : Cities[i].Loc_y;
        MinX = (MinX < Cities[i].Loc_x) ? MinX : Cities[i].Loc_x;
        MinY = (MinY < Cities[i].Loc_y) ? MinY : Cities[i].Loc_y;
    }
}

//画出所有的点和边
void Graph::drawPoint(QGraphicsScene *Scene)
{
    Scene->clear();

    Scene->setSceneRect(0, 0, 748, 498);

    //画出点
    int length = Cities.size();

    MapEdge();

    double LocX,LocY;
    QString CityName;
    double padding = 50;
    for (int i = 0;i < length;i++)
    {
        LocX = Cities[i].Loc_x;
        LocY = Cities[i].Loc_y;
        CityName = Cities[i].name;

        //进行缩放
        LocX = padding + (LocX - MinX) / (MaxX - MinX) * (748 - 2 * padding);
        LocY = padding + (1 - (LocY - MinY) / (MaxY - MinY)) * (498 - 2 * padding);

        Scene->addEllipse(LocX - 15, LocY - 15, 30, 30, QPen(Qt::black), QBrush(Qt::cyan));
        Scene->addText(CityName)->setPos(LocX - 15, LocY - 12);
    }

    //画出边
    length = Edges.size();
    double LocX_end,LocY_end;
    for (int i = 0;i < length;i++)
    {
        LocX = Edges[i].BeginCity->Loc_x;
        LocY = Edges[i].BeginCity->Loc_y;
        LocX_end = Edges[i].EndCity->Loc_x;
        LocY_end = Edges[i].EndCity->Loc_y;

        //进行缩放
        LocX = padding + (LocX - MinX) / (MaxX - MinX) * (748 - 2 * padding);
        LocY = padding + (1 - (LocY - MinY) / (MaxY - MinY)) * (498 - 2 * padding);
        LocX_end = padding + (LocX_end - MinX) / (MaxX - MinX) * (748 - 2 * padding);
        LocY_end = padding + (1 - (LocY_end - MinY) / (MaxY - MinY)) * (498 - 2 * padding);

        Scene->addLine(LocX, LocY, LocX_end, LocY_end, QPen(Qt::black));
        Scene->addText(QString::number(Edges[i].weidgt))->setPos((LocX + LocX_end) / 2,(LocY + LocY_end) / 2);
    }
}

//通过名字找到序号
int Graph::FindCityIndex(QString CityName)
{
    int length = Cities.size();
    for (int i = 0;i < length;i++)
    {
        if (Cities[i].name == CityName)
            return i;
    }
    return -1;
}

//查找最短路径算法
std::vector<int> Graph::ShortestPath(int src, int dst, int &outDist)
{
    std::vector<int> path;

    int n = Cities.size();
    if (src < 0 || src >= n || dst < 0 || dst >= n) {
        outDist = -1;
        return path;
    }

    // 构造邻接表（索引为 Cities 的位置）
    std::vector<std::vector<std::pair<int,int>>> adj(n);
    for (const auto &e : Edges) {
        int u = -1, v = -1;
        // 找索引（通过地址比较）
        for (int i = 0; i < n; ++i) {
            if (&Cities[i] == e.BeginCity) u = i;
            if (&Cities[i] == e.EndCity) v = i;
            if (u != -1 && v != -1) break;
        }
        if (u == -1 || v == -1) continue;
        adj[u].push_back({v, e.weidgt});
        adj[v].push_back({u, e.weidgt}); // 双向
    }

    const int INF = std::numeric_limits<int>::max() / 4;
    std::vector<int> dist(n, INF);
    std::vector<int> prev(n, -1);

    // min-heap, pair<dist, node>
    using P = std::pair<int,int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        int d = cur.first;
        int u = cur.second;
        if (d > dist[u]) continue;
        if (u == dst) break;

        for (const auto &pr : adj[u]) {
            int v = pr.first;
            int w = pr.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[dst] >= INF) {
        outDist = -1;
        return path;
    }

    outDist = dist[dst];
    // 重建路径
    for (int v = dst; v != -1; v = prev[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

//外部调用方法
void Graph::PathSearch(QComboBox *BeginPoint, QComboBox *EndPoint, QTextBrowser *Path, QTextBrowser *Long)
{
    int BeginIndex = FindCityIndex(BeginPoint->currentText());
    int Endindex = FindCityIndex(EndPoint->currentText());

    int dist;

    auto path = ShortestPath(BeginIndex, Endindex, dist);

    if (path.empty()) {
        Path->setText("两地之间没有路径！");
        return;
    }

    QString str = "最短路径:";
    for (int index : path)
        str += Cities[index].name + "->";
    str.chop(2);
    Path->setText(str);
    Long->setText(QString("总距离：%1").arg(dist));

    for (int index : path)
    {

    }
}
