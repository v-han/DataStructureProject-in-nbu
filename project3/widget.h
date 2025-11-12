#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>

#include "mazes.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    Mazes Maze;

    void ChangeButton(QPushButton* button);
    bool MoveMaze(int posI,int posJ);
    QPushButton* PosToButton(int posI,int posJ);
    void Reflesh();
};
#endif // WIDGET_H
