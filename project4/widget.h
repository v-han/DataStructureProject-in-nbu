#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>

#include "binarytree.h"

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

    BinaryTree Tree;
    QGraphicsScene *scene = new QGraphicsScene(this);

    void TreeInsert();
    void TreeClear();
    void TreeDelete();
    void TreeDraw();
    void NodeDraw(TreeNode *Nodeptr,int x,int y,int offset);
};
#endif // WIDGET_H
