#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->ButtonInsert,&QPushButton::clicked,this,[this](){TreeInsert();});
    connect(ui->ButtonClear,&QPushButton::clicked,this,[this](){TreeClear();});
    connect(ui->ButtonDelete,&QPushButton::clicked,this,[this](){TreeDelete();});
}

Widget::~Widget()
{
    delete ui;
}

void Widget::TreeInsert()
{
    int num = ui->lineEdit->text().toInt();
    ui->lineEdit->clear();

    Tree.TreeInsert(num);

    QString str = Tree.inorderPrintOut();
    ui->textBrowser->setHtml(QString("<p style = 'font-size:20px'>%1</p>").arg(str));
    TreeDraw();
}

void Widget::TreeDraw()
{
    scene->clear();

    scene->setSceneRect(-349, -99, 698, 398);

    NodeDraw(Tree.getRootNode(), 0, 0, 698/4);

    ui->graphicsView->setScene(scene);
    //ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

void Widget::NodeDraw(TreeNode* Nodeptr,int x,int y,int offset)
{
    if (!Nodeptr)
        return;
    //画出节点
    scene->addEllipse(x - 15, y - 15, 30, 30, QPen(Qt::black), QBrush(Qt::cyan));
    scene->addText(QString::number(Nodeptr->num))->setPos(x - 8, y - 10);

    //画出左子树
    if (Nodeptr->LNode)
    {
        scene->addLine(x, y, x - offset, y + 60);
        NodeDraw(Nodeptr->LNode, x - offset, y + 60, offset / 2);
    }

    //画出右子树
    if (Nodeptr->RNode)
    {
        scene->addLine(x, y, x + offset, y + 60);
        NodeDraw(Nodeptr->RNode, x + offset, y + 60, offset / 2);
    }

}

void Widget::TreeClear()
{
    Tree.TreeClear();

    ui->textBrowser->setHtml(QString("<p style = 'font-size:20px'></p>"));
    TreeDraw();
}

void Widget::TreeDelete()
{
    int num = ui->lineEdit->text().toInt();
    ui->lineEdit->clear();

    Tree.TreeDelete(num);
    QString str = Tree.inorderPrintOut();
    ui->textBrowser->setHtml(QString("<p style = 'font-size:20px'>%1</p>").arg(str));
    TreeDraw();
}
